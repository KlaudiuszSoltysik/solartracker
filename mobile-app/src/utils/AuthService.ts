import * as SecureStore from 'expo-secure-store';
import { refreshAsync, TokenResponse, revokeAsync } from 'expo-auth-session';

const TOKEN_KEY = 'solartracker_tokens';

export const saveTokens = async (tokenResponse) => {
    try {
        await SecureStore.setItemAsync(TOKEN_KEY, JSON.stringify(tokenResponse));
    } catch (error) {
    }
};

export const clearTokens = async () => {
    try {
        await SecureStore.deleteItemAsync(TOKEN_KEY);
    } catch (error) {
    }
};

export const getValidTokens = async (discovery, clientId) => {
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

export const performServerLogout = async (discovery, clientId) => {
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
    } finally {
        await clearTokens();
    }
};