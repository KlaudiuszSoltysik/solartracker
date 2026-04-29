export type RootStackParamList = {
    Home: undefined;
    Asset: {
        deviceId: string;
        assetType: string;
        name: string;
        maxPowerW: number;
        lat: number;
        lon: number;
    };
};