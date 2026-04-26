import React, {useEffect, useState} from "react";
import {ActivityIndicator, Dimensions, ScrollView, StyleSheet, Text, TouchableOpacity, View} from "react-native";
import {
    VictoryAxis,
    VictoryChart,
    VictoryLine,
    VictoryScatter,
    VictoryTheme,
    VictoryZoomContainer
} from "victory-native";
import {API_BASE_URL} from "../../App";

export default function AssetScreen({route}: any) {
    const {deviceId, assetType, name, maxPowerW, lat, lon} = route.params;

    const [currentDate, setCurrentDate] = useState(new Date());
    const [loading, setLoading] = useState(false);

    const [data, setData] = useState({
        power: { real: [], forecast: [] },
        irradiance: { real: [], forecast: [] },
        temp: { real: [], forecast: [] },
        wind: { real: [], forecast: [] }
    });

    const handlePreviousDay = () => {
        const prev = new Date(currentDate);
        prev.setDate(prev.getDate() - 1);
        setCurrentDate(prev);
    };

    const handleNextDay = () => {
        const next = new Date(currentDate);
        next.setDate(next.getDate() + 1);
        setCurrentDate(next);
    };

    const handleToday = () => {
        setCurrentDate(new Date());
    };

    const year = currentDate.getFullYear();
    const month = String(currentDate.getMonth() + 1).padStart(2, "0");
    const day = String(currentDate.getDate()).padStart(2, "0");
    const formattedDate = `${year}-${month}-${day}`;

    const isToday = new Date().toDateString() === currentDate.toDateString();

    const getTimeBounds = () => {
        const start = new Date(currentDate);
        start.setUTCHours(0, 0, 0, 0);

        const end = new Date(currentDate);
        end.setUTCHours(23, 59, 59, 999);

        return `?start_date=${start.toISOString()}&end_date=${end.toISOString()}`;
    };

    const extractData = (json: any, key: string) =>
        (json.data || []).map((d: any) => ({
            x: new Date(d.time),
            y: d[key] ?? 0
        }));

    const fetchTelemetryData = async (params: string) => {
        try {
            const res = await fetch(`${API_BASE_URL}/telemetry/${deviceId}${params}`);
            const json = await res.json();

            setData(prev => ({
                ...prev,
                power: {...prev.power, real: extractData(json, "power_w")},
                irradiance: {...prev.irradiance, real: extractData(json, "irradiance_wm2")},
                temp: {...prev.temp, real: extractData(json, "temp_c")},
                wind: {...prev.wind, real: extractData(json, "wind_mps")}
            }));
        } catch (err) {
            console.error("Failed to fetch telemetry:", err);
        }
    };

    const fetchForecastData = async (params: string) => {
        try {
            const res = await fetch(`${API_BASE_URL}/energy-forecast/${deviceId}${params}`);
            const json = await res.json();

            setData(prev => ({
                ...prev,
                power: {...prev.power, forecast: extractData(json, "power_w")},
                irradiance: {...prev.irradiance, forecast: extractData(json, "irradiance_wm2")},
                temp: {...prev.temp, forecast: extractData(json, "temp_c")},
                wind: {...prev.wind, forecast: extractData(json, "wind_speed_mps")}
            }));
        } catch (err) {
            console.error("Failed to fetch forecast:", err);
        }
    };

    useEffect(() => {
        const loadAllData = async () => {
            setLoading(true);
            const params = getTimeBounds();
            await Promise.all([
                fetchTelemetryData(params),
                fetchForecastData(params)
            ]);
            setLoading(false);
        };

        loadAllData();
    }, [currentDate]);


    useEffect(() => {
        if (!isToday) return;

        let ws: WebSocket;
        let reconnectTimer: NodeJS.Timeout;

        const connectWebSocket = () => {
            const WS_BASE_URL = API_BASE_URL.replace(/^http/, 'ws');

            ws = new WebSocket(`${WS_BASE_URL}/ws/live/${deviceId}`);

            ws.onopen = () => console.log(`WS connected for ${deviceId}`);

            ws.onmessage = (event) => {
                const msg = JSON.parse(event.data);

                if (msg.type === "live_telemetry") {
                    setData(prev => {
                        const newTime = new Date(msg.time);
                        return {
                            ...prev,
                            power: {...prev.power, real: [...prev.power.real, {x: newTime, y: msg.power_w ?? 0}]},
                            irradiance: {
                                ...prev.irradiance,
                                real: [...prev.irradiance.real, {x: newTime, y: msg.irradiance_wm2 ?? 0}]
                            },
                            temp: {...prev.temp, real: [...prev.temp.real, {x: newTime, y: msg.temp_c ?? 0}]},
                            wind: {...prev.wind, real: [...prev.wind.real, {x: newTime, y: msg.wind_mps ?? 0}]},
                        };
                    });
                } else if (msg.type === "forecast_update") {
                    console.log("Received forecast update ping! Refetching forecast lines...");
                    const params = getTimeBounds();
                    fetchForecastData(params);
                }
            };

            ws.onerror = (e) => console.log("WS Error", e);

            ws.onclose = () => {
                console.log("WS Closed. Attempting reconnect in 5s...");
                reconnectTimer = setTimeout(connectWebSocket, 5000);
            };
        };

        connectWebSocket();

        return () => {
            clearTimeout(reconnectTimer);
            if (ws) ws.close();
        };
    }, [currentDate, deviceId, isToday]);

    return (
        <ScrollView style={styles.container} contentContainerStyle={{paddingBottom: 40}}>
            <View style={styles.metaCard}>
                <Text style={styles.metaTitle}>{name} <Text style={styles.metaBadge}>({assetType.toUpperCase()})</Text></Text>
                <View style={styles.metaRow}>
                    <Text style={styles.metaLabel}>Installed power:</Text>
                    <Text style={styles.metaValue}>{maxPowerW} W</Text>
                </View>
                <View style={styles.metaRow}>
                    <Text style={styles.metaLabel}>Localization:</Text>
                    <Text style={styles.metaValue}>{lat.toFixed(4)}, {lon.toFixed(4)}</Text>
                </View>
                <View style={styles.metaRow}>
                    <Text style={styles.metaLabel}>Device ID:</Text>
                    <Text style={styles.metaValue}>{deviceId}</Text>
                </View>
            </View>

            <View style={styles.dateControlContainer}>
                <View style={styles.dateButtonsRow}>
                    <TouchableOpacity style={styles.dateBtn} onPress={handlePreviousDay}>
                        <Text style={styles.dateBtnText}>{"< Prev"}</Text>
                    </TouchableOpacity>

                    <TouchableOpacity style={styles.dateBtnToday} onPress={handleToday}>
                        <Text style={styles.dateBtnTextToday}>Today</Text>
                    </TouchableOpacity>

                    <TouchableOpacity style={styles.dateBtn} onPress={handleNextDay}>
                        <Text style={styles.dateBtnText}>{"Next >"}</Text>
                    </TouchableOpacity>
                </View>
                <Text style={styles.currentDateText}>{formattedDate}</Text>
            </View>

            {loading ? (
                <ActivityIndicator size="large" color="#8641f4" style={{marginTop: 50}}/>
            ) : (
                data && (
                    <>
                        <MetricChart
                            title="Power"
                            realData={data.power.real}
                            forecastData={data.power.forecast}
                            ySuffix=" W"
                            isToday={isToday}
                        />

                        {assetType.toLowerCase() === "pv" && (
                            <>
                                <MetricChart
                                    title="Shortwave radiation"
                                    realData={data.irradiance.real}
                                    forecastData={data.irradiance.forecast}
                                    ySuffix=" W/m²"
                                    isToday={isToday}
                                />
                                <MetricChart
                                    title="Air temperature"
                                    realData={data.temp.real}
                                    forecastData={data.temp.forecast}
                                    ySuffix="°C"
                                    isToday={isToday}
                                />
                            </>
                        )}

                        {assetType.toLowerCase() === "wind" && (
                            <MetricChart
                                title="Wind speed"
                                realData={data.wind.real}
                                forecastData={data.wind.forecast}
                                ySuffix=" m/s"
                                isToday={isToday}
                            />
                        )}
                    </>
                )
            )}
        </ScrollView>
    );
}

const MetricChart = ({title, realData, forecastData, ySuffix, isToday}: {
    title: string,
    realData: any[],
    forecastData: any[],
    ySuffix: string,
    isToday?: boolean
}) => {
    const now = new Date();

    return (
        <View style={styles.chartCard}>
            <Text style={styles.chartTitle}>{title}</Text>
            <VictoryChart
                theme={VictoryTheme.material}
                width={Dimensions.get("window").width - 32}
                height={250}
                scale={{x: "time"}}
                domainPadding={{y: 20}}
                padding={{top: 20, bottom: 40, left: 75, right: 20}}
                containerComponent={<VictoryZoomContainer zoomDimension="x" allowZoom={true} allowPan={true}/>}
            >
                <VictoryAxis
                    tickFormat={(x) => {
                        const d = new Date(x);
                        return `${d.getHours()}:${d.getMinutes().toString().padStart(2, "0")}`;
                    }}
                    fixLabelOverlap
                    style={{tickLabels: {fontSize: 10, padding: 5}}}
                />

                <VictoryAxis dependentAxis tickFormat={(x) => `${Math.round(x)}${ySuffix}`}/>

                {isToday && (
                    <VictoryAxis
                        dependentAxis
                        axisValue={now}
                        style={{
                            axis: {stroke: "#ff4757", strokeWidth: 1.5, strokeDasharray: "5,5"},
                            tickLabels: {fill: "transparent"},
                            ticks: {stroke: "transparent"},
                            grid: {stroke: "transparent"}
                        }}
                    />
                )}

                {forecastData && forecastData.length > 0 && (
                    <VictoryLine data={forecastData} style={{data: {stroke: "#8641f4", strokeWidth: 2}}}/>
                )}

                {realData && realData.length > 0 && (
                    <VictoryLine data={realData} style={{data: {stroke: "#22c1c3", strokeWidth: 2}}}/>
                )}

                {realData && realData.length > 0 && (
                    <VictoryScatter data={realData} size={2} style={{data: {fill: "#22c1c3"}}}/>
                )}
            </VictoryChart>
        </View>
    );
};

const styles = StyleSheet.create({
    container: {flex: 1, backgroundColor: "#f5f5f5", padding: 16},

    metaCard: {
        backgroundColor: "white",
        borderRadius: 16,
        padding: 16,
        marginBottom: 16,
        elevation: 3,
        shadowColor: "#000",
        shadowOpacity: 0.1,
        shadowRadius: 5,
        shadowOffset: {width: 0, height: 2}
    },
    metaTitle: {fontSize: 22, fontWeight: "bold", color: "#333", marginBottom: 12},
    metaBadge: {fontSize: 14, color: "#8641f4", fontWeight: "normal"},
    metaRow: {
        flexDirection: "row",
        justifyContent: "space-between",
        paddingVertical: 4,
        borderBottomWidth: 1,
        borderBottomColor: "#f0f0f0"
    },
    metaLabel: {fontSize: 14, color: "#666"},
    metaValue: {fontSize: 14, fontWeight: "600", color: "#333"},

    chartCard: {
        backgroundColor: "white",
        borderRadius: 16,
        padding: 8,
        marginBottom: 16,
        elevation: 3,
        shadowColor: "#000",
        shadowOpacity: 0.1,
        shadowRadius: 5,
        shadowOffset: {width: 0, height: 2}
    },
    chartTitle: {fontSize: 16, fontWeight: "bold", color: "#444", textAlign: "center", marginTop: 8, marginBottom: -10},

    dateControlContainer: {marginBottom: 16, alignItems: "center"},
    dateButtonsRow: {flexDirection: "row", justifyContent: "space-between", width: "100%", marginBottom: 8},
    dateBtn: {
        backgroundColor: "#e0e0e0",
        paddingVertical: 8,
        paddingHorizontal: 16,
        borderRadius: 8,
        minWidth: 80,
        alignItems: "center"
    },
    dateBtnText: {color: "#333", fontWeight: "600"},
    dateBtnToday: {
        backgroundColor: "#8641f4",
        paddingVertical: 8,
        paddingHorizontal: 24,
        borderRadius: 8,
        elevation: 2
    },
    dateBtnTextToday: {color: "white", fontWeight: "bold"},
    currentDateText: {fontSize: 16, fontWeight: "bold", color: "#555"}
});