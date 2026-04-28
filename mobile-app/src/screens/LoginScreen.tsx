import React, { useState, useEffect } from "react";
import { View, Text, StyleSheet, TouchableOpacity, ActivityIndicator, Alert } from "react-native";
import * as WebBrowser from "expo-web-browser";
import { useAuthRequest, useAutoDiscovery, exchangeCodeAsync, makeRedirectUri } from "expo-auth-session";

WebBrowser.maybeCompleteAuthSession();

const KEYCLOAK_URL = "https://auth.260824.xyz/realms/solartracker";
const CLIENT_ID = "mobile-app";

const LoginScreen = ({ onLoginSuccess }) => {
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
                            extraParams: request.codeVerifier ? { code_verifier: request.codeVerifier } : undefined,
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
                    <ActivityIndicator size="large" color="#f39c12" />
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
        backgroundColor: "#1e272e",
        justifyContent: "space-between",
        padding: 30,
    },
    header: {
        marginTop: 100,
        alignItems: "center",
    },
    title: {
        fontSize: 42,
        fontWeight: "bold",
        color: "#f39c12",
    },
    footer: {
        marginBottom: 50,
    },
    button: {
        backgroundColor: "#f39c12",
        paddingVertical: 15,
        borderRadius: 25,
        alignItems: "center",
        shadowColor: "#000",
        shadowOffset: { width: 0, height: 4 },
        shadowOpacity: 0.3,
        shadowRadius: 5,
        elevation: 8,
    },
    buttonText: {
        color: "#fff",
        fontSize: 18,
        fontWeight: "bold",
    },
});

export default LoginScreen;