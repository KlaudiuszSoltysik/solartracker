import * as SecureStore from 'expo-secure-store';
import { refreshAsync, TokenResponse, revokeAsync, DiscoveryDocument } from 'expo-auth-session';
import { Alert } from 'react-native';

const TOKEN_KEY = 'solartracker_tokens';

export const saveTokens = async (tokenResponse: TokenResponse) => {
    try {
        await SecureStore.setItemAsync(TOKEN_KEY, JSON.stringify(tokenResponse));
    } catch (error) {
        Alert.alert("Storage Error", "Failed to save session securely.");
    }
};

export const clearTokens = async () => {
    try {
        await SecureStore.deleteItemAsync(TOKEN_KEY);
    } catch (error) {
        Alert.alert("Storage Error", "Failed to clear session.");
    }
};

export const getValidTokens = async (discovery: DiscoveryDocument, clientId: string) => {
    try {
        const storedTokensString = await SecureStore.getItemAsync(TOKEN_KEY);
        if (!storedTokensString) return null;

        const storedTokens = JSON.parse(storedTokensString);
        const tokenResponse = new TokenResponse(storedTokens);

        if (tokenResponse.shouldRefresh()) {
            try {
                const refreshedTokens = await refreshAsync(
                    {
                        clientId: clientId,
                        refreshToken: tokenResponse.refreshToken,
                    },
                    discovery
                );
                await saveTokens(refreshedTokens);
                return refreshedTokens;
            } catch (refreshError) {
                await clearTokens();
                return null;
            }
        }
        return tokenResponse;
    } catch (error) {
        return null;
    }
};

export const performServerLogout = async (discovery: DiscoveryDocument, clientId: string) => {
    try {
        const storedTokensString = await SecureStore.getItemAsync(TOKEN_KEY);
        if (storedTokensString && discovery) {
            const storedTokens = JSON.parse(storedTokensString);

            await revokeAsync({
                clientId: clientId,
                token: storedTokens.accessToken
            }, discovery);

            await revokeAsync({
                clientId: clientId,
                token: storedTokens.refreshToken
            }, discovery);
        }
    } catch (error) {
        Alert.alert("Logout Warning", "Failed to revoke token on the server, but local session will be cleared.");
    } finally {
        await clearTokens();
    }
};