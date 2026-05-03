import React, { useEffect, useState } from "react";
import { ActivityIndicator, View } from "react-native";
import { NavigationContainer } from "@react-navigation/native";
import { createStackNavigator } from "@react-navigation/stack";
import { getValidTokens, saveTokens } from "./src/utils/AuthService";
import HomeScreen from "./src/screens/HomeScreen";
import AssetScreen from "./src/screens/AssetScreen";
import LoginScreen from "./src/screens/LoginScreen";
import { Platform, Alert } from 'react-native';
import * as Device from 'expo-device';
import * as Notifications from 'expo-notifications';
import Constants from 'expo-constants';
import * as LocalAuthentication from 'expo-local-authentication';

// export const API_BASE_URL = "https://6c3b-188-33-128-213.ngrok-free.app/api/v1";
// export const API_BASE_URL = "http://localhost:8001/api/v1";
export const API_BASE_URL = "https://api.260824.xyz/api/v1";

export const DISCOVERY = {
    authorizationEndpoint: "https://auth.260824.xyz/realms/solartracker/protocol/openid-connect/auth",
    tokenEndpoint: "https://auth.260824.xyz/realms/solartracker/protocol/openid-connect/token",
    revocationEndpoint: "https://auth.260824.xyz/realms/solartracker/protocol/openid-connect/revoke"
};

const CLIENT_ID = "mobile-app";

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

    useEffect(() => {
        async function registerForPushNotificationsAsync() {
            let token: string | undefined;

            if (Device.isDevice) {
                const { status: existingStatus } = await Notifications.getPermissionsAsync();
                let finalStatus = existingStatus;

                if (existingStatus !== 'granted') {
                    const { status } = await Notifications.requestPermissionsAsync();
                    finalStatus = status;
                }

                if (finalStatus !== 'granted') {
                    Alert.alert('Error', 'No permission for notifications!');
                    return;
                }

                try {
                    const projectId = Constants.expoConfig?.extra?.eas?.projectId;

                    token = (await Notifications.getExpoPushTokenAsync({
                        projectId: projectId,
                    })).data;

                    console.error("=====================================");
                    console.error("EXPO TOKEN:");
                    console.error(token);
                    console.error("=====================================");
                    Alert.alert("EXPO TOKEN", token);
                } catch (e) {
                }
            }

            if (Platform.OS === 'android') {
                await Notifications.setNotificationChannelAsync('default', {
                    name: 'default',
                    importance: Notifications.AndroidImportance.MAX,
                    vibrationPattern: [0, 250, 250, 250],
                    lightColor: '#FF4757',
                });
            }

            return token;
        }

        const checkAuth = async () => {
            const validTokens = await getValidTokens(DISCOVERY, CLIENT_ID);

            if (validTokens) {
                const hasHardware = await LocalAuthentication.hasHardwareAsync();
                const isEnrolled = await LocalAuthentication.isEnrolledAsync();

                if (hasHardware && isEnrolled) {
                    const authResult = await LocalAuthentication.authenticateAsync({
                        promptMessage: "Unlock SolarTracker",
                        fallbackLabel: "Use PIN",
                        cancelLabel: "Cancel",
                    });

                    if (authResult.success) {
                        setIsAuthenticated(true);
                    } else {
                        setIsAuthenticated(false);
                    }
                } else {
                    setIsAuthenticated(false);
                }
            } else {
                setIsAuthenticated(false);
            }
            setIsReady(true);
        };

        registerForPushNotificationsAsync();
        checkAuth();
    }, []);

    const handleLoginSuccess = async (tokenResponse: any) => {
        await saveTokens(tokenResponse);
        setIsAuthenticated(true);
    };

    const handleLogout = async () => {
        setIsAuthenticated(false);
        return;
    };

    if (!isReady) {
        return (
            <View style={{ flex: 1, justifyContent: "center", alignItems: "center", backgroundColor: "#1e272e" }}>
                <ActivityIndicator size="large" color="#f39c12" />
            </View>
        );
    }

    return (
        <NavigationContainer>
            <Stack.Navigator>
                {isAuthenticated ? (
                    <>
                        <Stack.Screen
                            name="Home"
                            options={{ headerShown: false }}
                        >
                            {(props) => <HomeScreen {...props} onLogout={handleLogout} />}
                        </Stack.Screen>

                        <Stack.Screen
                            name="Asset"
                            component={AssetScreen}
                            options={{ headerShown: false }}
                        />
                    </>
                ) : (
                    <Stack.Screen
                        name="Login"
                        options={{ headerShown: false }}
                    >
                        {(props) => <LoginScreen {...props} onLoginSuccess={handleLoginSuccess} />}
                    </Stack.Screen>
                )}
            </Stack.Navigator>
        </NavigationContainer>
    );
}