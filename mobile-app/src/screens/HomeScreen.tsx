import React, {useEffect, useState} from "react";
import {ActivityIndicator, FlatList, StyleSheet, Text, TouchableOpacity, View} from "react-native";
import {NativeStackNavigationProp} from "@react-navigation/native-stack";
import {RootStackParamList} from "../navigation/types";
import {API_BASE_URL} from "../../App";
import MapView, {Marker} from "react-native-maps";

type Props = {
    navigation: NativeStackNavigationProp<RootStackParamList, "Home">;
};

export default function HomeScreen({navigation}: Props) {
    const [assets, setAssets] = useState<any[]>([]);
    const [loading, setLoading] = useState(true);
    const [viewMode, setViewMode] = useState<"list" | "map">("list");
    const [selectedAsset, setSelectedAsset] = useState<any>(null);

    useEffect(() => {
        fetch(`${API_BASE_URL}/assets`)
            .then(res => res.json())
            .then(json => {
                setAssets(json);
                setLoading(false);
            })
            .catch(err => {
                console.error(err);
                setLoading(false);
            });
    }, []);

    if (loading) {
        return <ActivityIndicator size="large" style={styles.center}/>;
    }

    const initialRegion = assets.length > 0 ? {
        latitude: assets[0].lat,
        longitude: assets[0].lon,
        latitudeDelta: 0.5,
        longitudeDelta: 0.5,
    } : undefined;

    return (
        <View style={styles.container}>
            <View style={styles.toggleContainer}>
                <TouchableOpacity
                    style={[styles.toggleBtn, viewMode === "list" && styles.toggleActive]}
                    onPress={() => setViewMode("list")}
                >
                    <Text style={[styles.toggleText, viewMode === "list" && styles.toggleTextActive]}>List</Text>
                </TouchableOpacity>

                <TouchableOpacity
                    style={[styles.toggleBtn, viewMode === "map" && styles.toggleActive]}
                    onPress={() => setViewMode("map")}
                >
                    <Text style={[styles.toggleText, viewMode === "map" && styles.toggleTextActive]}>Map</Text>
                </TouchableOpacity>
            </View>

            {viewMode === "list" && (
                <FlatList
                    data={assets}
                    contentContainerStyle={{paddingBottom: 20}}
                    keyExtractor={(item, index) => item.device_id || index.toString()}
                    renderItem={({item}) => (
                        <TouchableOpacity
                            style={styles.listCard}
                            activeOpacity={0.9}
                            onPress={() => navigation.navigate("Asset", {
                                deviceId: item.device_id,
                                assetType: item.asset_type,
                                name: item.farm_name,
                                maxPowerW: item.max_power_w,
                                lat: item.lat,
                                lon: item.lon
                            })}
                        >
                            <View style={styles.cardContent}>
                                <View>
                                    <Text style={styles.cardTitle}>{item.farm_name}</Text>
                                    <Text style={styles.cardSubtitle}>
                                        {item.max_power_w} W • {item.asset_type === "pv" ? "☀️ Solar" : "🌬️ Wind"}
                                    </Text>
                                </View>
                                <Text style={styles.cardArrow}>➔</Text>
                            </View>
                        </TouchableOpacity>
                    )}
                />
            )}

            {viewMode === "map" && assets.length > 0 && (
                <View style={styles.mapContainer}>
                    <MapView
                        style={styles.map}
                        initialRegion={initialRegion}
                        onPress={() => setSelectedAsset(null)}
                    >
                        {assets.map((item) => (
                            <Marker
                                key={item.device_id}
                                coordinate={{latitude: item.lat, longitude: item.lon}}
                                anchor={{x: 0.25, y: 0.25}}
                                onPress={(e) => {
                                    e.stopPropagation();
                                    setSelectedAsset(item);
                                }}
                            >
                                <View style={{width: 40, height: 40, justifyContent: "center", alignItems: "center"}}>
                                    <View style={styles.customMarker}>
                                        <Text style={styles.markerEmoji}>
                                            {item.asset_type === "pv" ? "☀️" : "🌬️"}
                                        </Text>
                                    </View>
                                </View>
                            </Marker>
                        ))}
                    </MapView>

                    {selectedAsset && (
                        <TouchableOpacity
                            style={styles.floatingCard}
                            activeOpacity={0.9}
                            onPress={() => navigation.navigate("Asset", {
                                deviceId: selectedAsset.device_id,
                                assetType: selectedAsset.asset_type,
                                name: selectedAsset.farm_name,
                                maxPowerW: selectedAsset.max_power_w,
                                lat: selectedAsset.lat,
                                lon: selectedAsset.lon
                            })}
                        >
                            <View style={styles.cardContent}>
                                <View>
                                    <Text style={styles.title}>{selectedAsset.farm_name}</Text>
                                    <Text>{selectedAsset.max_power_w} W</Text>
                                    <Text>{selectedAsset.asset_type === "pv" ? "☀️ Solar" : "🌬️ Wind"}</Text>
                                </View>
                                <Text style={styles.cardArrow}>➔</Text>
                            </View>
                        </TouchableOpacity>
                    )}
                </View>
            )}
        </View>
    );
}

const styles = StyleSheet.create({
    container: {flex: 1, padding: 16, backgroundColor: "#f5f5f5"},
    center: {flex: 1, justifyContent: "center", alignItems: "center"},

    card: {
        backgroundColor: "white",
        padding: 20,
        borderRadius: 12,
        marginBottom: 12,
        elevation: 3,
        shadowOpacity: 0.1,
        shadowRadius: 5
    },
    title: {fontSize: 18, fontWeight: "bold", marginBottom: 8},

    toggleContainer: {flexDirection: "row", backgroundColor: "#e0e0e0", borderRadius: 8, padding: 4, marginBottom: 16},
    toggleBtn: {flex: 1, paddingVertical: 10, alignItems: "center", borderRadius: 6},
    toggleActive: {backgroundColor: "white", elevation: 2, shadowOpacity: 0.1, shadowRadius: 2},
    toggleText: {fontSize: 16, color: "#666", fontWeight: "500"},
    toggleTextActive: {color: "#333", fontWeight: "bold"},

    mapContainer: {flex: 1, borderRadius: 12, overflow: "hidden"},
    map: {width: "100%", height: "100%"},

    customMarker: {
        backgroundColor: "white",
        width: 36,
        height: 36,
        borderRadius: 18,
        justifyContent: "center",
        alignItems: "center",
        elevation: 5,
        shadowColor: "#000",
        shadowOpacity: 0.2,
        shadowRadius: 3,
        shadowOffset: {width: 0, height: 2},
        borderWidth: 1,
        borderColor: "#e0e0e0"
    },
    markerEmoji: {
        fontSize: 18,
        textAlign: "center"
    },
    calloutBubble: {
        backgroundColor: "white",
        borderRadius: 12,
        padding: 12,
        width: 150,
        alignItems: "center",
        elevation: 5,
        shadowColor: "#000",
        shadowOpacity: 0.2,
        shadowRadius: 4,
        shadowOffset: {width: 0, height: 2},
        marginBottom: 10
    },
    calloutTitle: {fontWeight: "bold", fontSize: 16, marginBottom: 4, textAlign: "center"},
    calloutSubtitle: {color: "#666", marginBottom: 8, fontSize: 14},
    calloutLink: {color: "#8641f4", fontWeight: "bold"},

    listCard: {
        backgroundColor: "white",
        borderRadius: 15,
        padding: 16,
        marginBottom: 12,
        marginHorizontal: 4,
        elevation: 4,
        shadowColor: "#000",
        shadowOpacity: 0.1,
        shadowRadius: 5,
        shadowOffset: {width: 0, height: 2},
        borderWidth: 1,
        borderColor: "#eee",
    },
    floatingCard: {
        position: "absolute",
        bottom: 20,
        left: 20,
        right: 20,
        backgroundColor: "white",
        borderRadius: 15,
        padding: 16,
        elevation: 10,
        shadowColor: "#000",
        shadowOpacity: 0.2,
        shadowRadius: 10,
        shadowOffset: {width: 0, height: 5},
        borderWidth: 1,
        borderColor: "#eee"
    },
    cardContent: {
        flexDirection: "row",
        justifyContent: "space-between",
        alignItems: "center"
    },
    cardTitle: {
        fontSize: 18,
        fontWeight: "bold",
        color: "#333"
    },
    cardSubtitle: {
        fontSize: 14,
        color: "#666",
        marginTop: 4
    },
    cardArrow: {
        fontSize: 24,
        color: "#8641f4",
        fontWeight: "bold"
    }
});