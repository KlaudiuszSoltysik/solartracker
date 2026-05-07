import React, { useState, useEffect, useRef } from "react";
import { View, ActivityIndicator, Alert, Platform, AppState, AppStateStatus } from "react-native";
import { NavigationContainer } from "@react-navigation/native";
import { createStackNavigator } from "@react-navigation/stack";
import { getValidTokens, saveTokens, performServerLogout, clearTokens } from "./src/utils/AuthService";
import HomeScreen from "./src/screens/HomeScreen";
import AssetScreen from "./src/screens/AssetScreen";
import LoginScreen from "./src/screens/LoginScreen";
import * as Notifications from "expo-notifications";
import Constants from "expo-constants";
import * as LocalAuthentication from "expo-local-authentication";

export const API_BASE_URL = "https://api.260824.xyz/api/v1";

export const DISCOVERY = {
    authorizationEndpoint:
        "https://auth.260824.xyz/realms/solartracker/protocol/openid-connect/auth",
    tokenEndpoint:
        "https://auth.260824.xyz/realms/solartracker/protocol/openid-connect/token",
    revocationEndpoint:
        "https://auth.260824.xyz/realms/solartracker/protocol/openid-connect/revoke",
};

export const CLIENT_ID = "mobile-app";

const Stack = createStackNavigator();

Notifications.setNotificationHandler({
    handleNotification: async () => ({
        shouldShowAlert: true,
        shouldPlaySound: true,
        shouldSetBadge: false,
        shouldShowBanner: true,
        shouldShowList: true,
    }),
});

export default function App() {
    const [isReady, setIsReady] = useState(false);
    const [isAuthenticated, setIsAuthenticated] = useState(false);
    const [accessToken, setAccessToken] = useState<string | null>(null);
    const [expoPushToken, setExpoPushToken] = useState<string | null>(null);

    const appState = useRef(AppState.currentState);

    useEffect(() => {
        const subscription = AppState.addEventListener(
            "change",
            async (nextAppState: AppStateStatus) => {
                if (
                    appState.current.match(/inactive|background/) &&
                    nextAppState === "active"
                ) {
                    if (isAuthenticated) {
                        const hasHardware = await LocalAuthentication.hasHardwareAsync();
                        const isEnrolled = await LocalAuthentication.isEnrolledAsync();

                        if (hasHardware && isEnrolled) {
                            const authResult = await LocalAuthentication.authenticateAsync({
                                promptMessage: "Welcome back. Unlock SolarTracker",
                                fallbackLabel: "Use PIN",
                                cancelLabel: "Cancel",
                            });

                            if (!authResult.success) {
                                setIsAuthenticated(false);
                                setAccessToken(null);
                            }
                        }
                    }
                }
                appState.current = nextAppState;
            },
        );

        return () => {
            subscription.remove();
        };
    }, [isAuthenticated]);

    useEffect(() => {
        async function registerForPushNotificationsAsync() {
            try {
                const { status: existingStatus } =
                    await Notifications.getPermissionsAsync();
                let finalStatus = existingStatus;

                if (existingStatus !== "granted") {
                    const { status } = await Notifications.requestPermissionsAsync();
                    finalStatus = status;
                }

                if (finalStatus !== "granted") {
                    Alert.alert("Push Error", "Permission for notifications denied!");
                    return;
                }

                const projectId = Constants.expoConfig?.extra?.eas?.projectId;

                const tokenData = await Notifications.getExpoPushTokenAsync({
                    projectId: projectId,
                });

                setExpoPushToken(tokenData.data);

                if (Platform.OS === "android") {
                    await Notifications.setNotificationChannelAsync("default", {
                        name: "default",
                        importance: Notifications.AndroidImportance.MAX,
                        vibrationPattern: [0, 250, 250, 250],
                        lightColor: "#FF4757",
                    });
                }
            } catch (e) {
                Alert.alert("Push Setup Failed", String(e));
            }
        }

        const checkAuth = async () => {
            try {
                const validTokens = await getValidTokens(DISCOVERY, CLIENT_ID);

                if (!validTokens) {
                    setIsAuthenticated(false);
                    setAccessToken(null);
                    setIsReady(true);
                    return;
                }

                const hasHardware = await LocalAuthentication.hasHardwareAsync();
                const isEnrolled = await LocalAuthentication.isEnrolledAsync();

                if (!hasHardware || !isEnrolled) {
                    Alert.alert(
                        "Security Info",
                        "No biometrics enrolled. Please login manually.",
                    );
                    await clearTokens();
                    setIsAuthenticated(false);
                    setAccessToken(null);
                    setIsReady(true);
                    return;
                }

                const authResult = await LocalAuthentication.authenticateAsync({
                    promptMessage: "Unlock SolarTracker",
                    fallbackLabel: "Use PIN",
                    cancelLabel: "Cancel",
                });

                if (authResult.success) {
                    setIsAuthenticated(true);
                    setAccessToken(validTokens.accessToken);
                } else {
                    Alert.alert("Auth Failed", "Biometric verification failed.");
                    setIsAuthenticated(false);
                    setAccessToken(null);
                }
            } catch (e) {
                Alert.alert("Auth Check Error", String(e));
                setIsAuthenticated(false);
                setAccessToken(null);
            } finally {
                setIsReady(true);
            }
        };

        registerForPushNotificationsAsync();
        checkAuth();
    }, []);

    useEffect(() => {
        const sendTokenToServer = async () => {
            if (expoPushToken && accessToken) {
                try {
                    const response = await fetch(`${API_BASE_URL}/update-push-token`, {
                        method: "POST",
                        headers: {
                            "Content-Type": "application/json",
                            Authorization: `Bearer ${accessToken}`,
                        },
                        body: JSON.stringify({ token: expoPushToken }),
                    });

                    if (!response.ok) {
                        throw new Error(`Server responded with status ${response.status}`);
                    }
                } catch (error) {
                    Alert.alert(
                        "Push Token Error",
                        "Failed to send push token to server.",
                    );
                }
            }
        };

        sendTokenToServer();
    }, [expoPushToken, accessToken]);

    const handleLoginSuccess = async (tokenResponse: any) => {
        await saveTokens(tokenResponse);
        setAccessToken(tokenResponse.accessToken);
        setIsAuthenticated(true);
    };

    const handleLogout = async () => {
        await performServerLogout(DISCOVERY, CLIENT_ID);
        setAccessToken(null);
        setIsAuthenticated(false);
        Alert.alert("Logged Out", "Your session has been securely closed.");
    };

    if (!isReady) {
        return (
            <View
                style={{
                    flex: 1,
                    justifyContent: "center",
                    alignItems: "center",
                    backgroundColor: "#1e272e",
                }}
            >
                <ActivityIndicator size="large" color="#f39c12" />
            </View>
        );
    }

    return (
        <NavigationContainer>
            <Stack.Navigator>
                {isAuthenticated ? (
                    <>
                        <Stack.Screen name="Home" options={{ headerShown: false }}>
                            {(props) => (
                                <HomeScreen
                                    {...props}
                                    onLogout={handleLogout}
                                    accessToken={accessToken}
                                />
                            )}
                        </Stack.Screen>

                        <Stack.Screen name="Asset" options={{ headerShown: false }}>
                            {(props) => <AssetScreen {...props} accessToken={accessToken} />}
                        </Stack.Screen>
                    </>
                ) : (
                    <Stack.Screen name="Login" options={{ headerShown: false }}>
                        {(props) => (
                            <LoginScreen {...props} onLoginSuccess={handleLoginSuccess} />
                        )}
                    </Stack.Screen>
                )}
            </Stack.Navigator>
        </NavigationContainer>
    );
}
