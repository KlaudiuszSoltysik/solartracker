import React, {useEffect, useState} from 'react';
import {ActivityIndicator, FlatList, StyleSheet, Text, TouchableOpacity, View} from 'react-native';
import {NativeStackNavigationProp} from '@react-navigation/native-stack';
import {RootStackParamList} from '../navigation/types';
import {API_BASE_URL} from "../../App";

type Props = {
    navigation: NativeStackNavigationProp<RootStackParamList, 'Home'>;
};

export default function HomeScreen({navigation}: Props) {
    const [assets, setAssets] = useState<any[]>([]);
    const [loading, setLoading] = useState(true);

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

    return (
        <View style={styles.container}>
            <FlatList
                data={assets}
                keyExtractor={(item, index) => item.device_id || index.toString()}
                renderItem={({item}) => (
                    <TouchableOpacity
                        style={styles.card}
                        onPress={() => navigation.navigate('Asset', {
                            deviceId: item.device_id,
                            assetType: item.asset_type,
                            name: item.farm_name
                        })}
                    >
                        <Text style={styles.title}>{item.farm_name}</Text>
                        <Text>{item.asset_type === 'pv' ? '☀️ Solar' : '🌬️ Wind'}</Text>
                    </TouchableOpacity>
                )}
            />
        </View>
    );
}

const styles = StyleSheet.create({
    container: {flex: 1, padding: 16, backgroundColor: '#f5f5f5'},
    center: {flex: 1, justifyContent: 'center', alignItems: 'center'},
    card: {
        backgroundColor: 'white',
        padding: 20,
        borderRadius: 12,
        marginBottom: 12,
        elevation: 3,
        shadowOpacity: 0.1,
        shadowRadius: 5,
    },
    title: {fontSize: 18, fontWeight: 'bold', marginBottom: 8},
});