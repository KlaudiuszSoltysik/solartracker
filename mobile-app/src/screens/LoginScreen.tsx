import React, {useEffect, useState} from "react";
import {ActivityIndicator, Alert, StyleSheet, Text, TouchableOpacity, View} from "react-native";
import * as WebBrowser from "expo-web-browser";
import {exchangeCodeAsync, makeRedirectUri, useAuthRequest, useAutoDiscovery} from "expo-auth-session";

WebBrowser.maybeCompleteAuthSession();

const KEYCLOAK_URL = "https://auth.260824.xyz/realms/solartracker";
const CLIENT_ID = "mobile-app";

const LoginScreen = ({onLoginSuccess}) => {
    const [isLoading, setIsLoading] = useState(false);

    const discovery = useAutoDiscovery(KEYCLOAK_URL);

    const redirectUri = makeRedirectUri({
        scheme: "solartracker",
        path: "login-callback"
    });

    const [request, response, promptAsync] = useAuthRequest(
        {
            clientId: CLIENT_ID,
            scopes: ["openid", "profile", "offline_access"],
            redirectUri: redirectUri,
        },
        discovery
    );

    useEffect(() => {
        const fetchTokens = async () => {
            if (response?.type === "success") {
                setIsLoading(true);
                try {
                    const tokenResponse = await exchangeCodeAsync(
                        {
                            clientId: CLIENT_ID,
                            code: response.params.code,
                            extraParams: request.codeVerifier ? {code_verifier: request.codeVerifier} : undefined,
                            redirectUri: redirectUri,
                        },
                        discovery
                    );

                    onLoginSuccess(tokenResponse);

                } catch (error) {
                    Alert.alert("Error", error.message || "Something went wrong");
                } finally {
                    setIsLoading(false);
                }
            } else if (response?.type === "error") {
                Alert.alert("Error", response.error?.message || "Something went wrong");
            }
        };

        fetchTokens();
    }, [response, discovery, request]);

    return (
        <View style={styles.container}>
            <View style={styles.header}>
                <Text style={styles.title}>☀️ SolarTracker</Text>
            </View>

            <View style={styles.footer}>
                {isLoading || !discovery ? (
                    <ActivityIndicator size="large" color="#f39c12"/>
                ) : (
                    <TouchableOpacity
                        style={styles.button}
                        onPress={() => promptAsync()}
                        disabled={!request}
                    >
                        <Text style={styles.buttonText}>Log in!</Text>
                    </TouchableOpacity>
                )}
            </View>
        </View>
    );
};

const styles = StyleSheet.create({
    container: {
        flex: 1,
        backgroundColor: "#121212",
        justifyContent: "space-between",
        padding: 30,
    },
    header: {
        marginTop: 100,
        alignItems: "center",
    },
    title: {
        fontSize: 42,
        fontWeight: "900",
        color: "#FFB703",
        letterSpacing: 0.5,
    },
    footer: {
        marginBottom: 50,
    },
    button: {
        backgroundColor: "#FFB703",
        paddingVertical: 16,
        borderRadius: 30,
        alignItems: "center",
        justifyContent: "center",

        shadowColor: "#FFB703",
        shadowOffset: {width: 0, height: 4},
        shadowOpacity: 0.4,
        shadowRadius: 12,
        elevation: 8,
    },
    buttonText: {
        color: "#121212",
        fontSize: 18,
        fontWeight: "800",
        textTransform: "uppercase",
        letterSpacing: 1.5,
    },
});

export default LoginScreen;