import React, {useEffect, useState} from 'react';
import {ActivityIndicator, Button, Dimensions, StyleSheet, Text, View} from 'react-native';
import {LineChart} from 'react-native-chart-kit';
import {RouteProp} from '@react-navigation/native';
import {RootStackParamList} from '../navigation/types';
import {API_BASE_URL} from "../../App";

type Props = {
    route: RouteProp<RootStackParamList, 'Asset'>;
};

export default function AssetScreen({route}: Props) {
    const {deviceId, assetType} = route.params;
    const [currentDate, setCurrentDate] = useState(new Date());
    const [loading, setLoading] = useState(false);
    const [chartData, setChartData] = useState<any>(null);

    const fetchData = async () => {
        setLoading(true);

        const start = new Date(currentDate);
        start.setUTCHours(0, 0, 0, 0);

        const end = new Date(currentDate);
        end.setUTCHours(23, 59, 59, 999);

        const params = `?start_date=${start.toISOString()}&end_date=${end.toISOString()}`;

        try {
            const [realRes, forecastRes] = await Promise.all([
                fetch(`${API_BASE_URL}/telemetry/${deviceId}${params}`),
                fetch(`${API_BASE_URL}/energy-forecast/${deviceId}${params}`)
            ]);

            const realJson = await realRes.json();
            const forecastJson = await forecastRes.json();

            const realMap: Record<string, number> = {};
            if (realJson.data) {
                realJson.data.forEach((d: any) => { realMap[d.time] = d.power_w || 0; });
            }

            const forecastMap: Record<string, number> = {};
            if (forecastJson.data) {
                forecastJson.data.forEach((d: any) => { forecastMap[d.time] = d.power_w || 0; });
            }

            const allUniqueTimes = Array.from(new Set([
                ...Object.keys(realMap),
                ...Object.keys(forecastMap)
            ]));

            if (allUniqueTimes.length === 0) {
                setChartData(null);
                return;
            }

            const realValues = allUniqueTimes.map(t => realMap[t] !== undefined ? realMap[t] : 0);
            const forecastValues = allUniqueTimes.map(t => forecastMap[t] !== undefined ? forecastMap[t] : 0);

            const rawLabels = allUniqueTimes.map(t => t.split('T')[1].substring(0, 5));

            const step = Math.ceil(rawLabels.length / 6) || 1;
            const displayLabels = rawLabels.map((label, index) => index % step === 0 ? label : "");

            setChartData({
                labels: displayLabels,
                datasets: [
                    {
                        data: realValues,
                        color: (opacity = 1) => `rgba(34, 193, 195, ${opacity})`,
                        strokeWidth: 2
                    },
                    {
                        data: forecastValues,
                        color: (opacity = 1) => `rgba(134, 65, 244, ${opacity})`,
                        strokeWidth: 2
                    }
                ],
                legend: ["Real", "Forecast"]
            });
        } catch (err) {
            console.error("AssetScreen Fetch Error:", err);
            setChartData(null);
        } finally {
            setLoading(false);
        }
    };

    useEffect(() => {
        fetchData();
    }, [currentDate]);

    const changeDay = (offset: number) => {
        const nextDate = new Date(currentDate);
        nextDate.setUTCDate(nextDate.getUTCDate() + offset);
        setCurrentDate(nextDate);
    };

    const goToToday = () => {
        setCurrentDate(new Date());
    };

    const displayDate = currentDate.toISOString().split('T')[0];

    return (
        <View style={styles.container}>
            <View style={styles.metaBox}>
                <Text style={styles.metaText}>Device ID: {deviceId}</Text>
                <Text style={styles.metaText}>Type: {assetType.toUpperCase()}</Text>
                <Text style={styles.metaText}>Date: {displayDate} (UTC)</Text>
            </View>

            <View style={styles.controls}>
                <Button title="< Prev" onPress={() => changeDay(-1)} disabled={loading}/>
                <Button title="Today" onPress={goToToday} disabled={loading}/>
                <Button title="Next >" onPress={() => changeDay(1)} disabled={loading}/>
            </View>

            {loading ? (
                <ActivityIndicator size="large" style={{marginTop: 50}}/>
            ) : (
                chartData && (
                    <LineChart
                        data={chartData}
                        width={Dimensions.get("window").width - 32}
                        height={250}
                        chartConfig={{
                            backgroundColor: "#ffffff",
                            backgroundGradientFrom: "#ffffff",
                            backgroundGradientTo: "#ffffff",
                            decimalPlaces: 0,
                            color: (opacity = 1) => `rgba(0, 0, 0, ${opacity})`,
                            labelColor: (opacity = 1) => `rgba(0, 0, 0, ${opacity})`,
                            propsForDots: {r: "2"}
                        }}
                        bezier
                        style={styles.chart}
                    />
                )
            )}
        </View>
    );
}

const styles = StyleSheet.create({
    container: {flex: 1, padding: 16, backgroundColor: '#f5f5f5'},
    metaBox: {backgroundColor: 'white', padding: 16, borderRadius: 12, marginBottom: 20, elevation: 2},
    metaText: {fontSize: 16, marginBottom: 4},
    controls: {flexDirection: 'row', justifyContent: 'space-between', marginBottom: 20},
    chart: {borderRadius: 16}
});