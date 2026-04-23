import React from 'react';
import {NavigationContainer} from '@react-navigation/native';
import {createNativeStackNavigator} from '@react-navigation/native-stack';
import {RootStackParamList} from './src/navigation/types';

import HomeScreen from './src/screens/HomeScreen';
import AssetScreen from './src/screens/AssetScreen';

// export const API_BASE_URL = 'http://10.0.2.2:8001/api/v1';
export const API_BASE_URL = 'http://localhost:8001/api/v1';

const Stack = createNativeStackNavigator<RootStackParamList>();

export default function App() {
    return (
        <NavigationContainer>
            <Stack.Navigator initialRouteName="Home">
                <Stack.Screen
                    name="Home"
                    component={HomeScreen}
                    options={{title: 'Asset List'}}
                />
                <Stack.Screen
                    name="Asset"
                    component={AssetScreen}
                    options={({route}) => ({title: route.params.name || 'Asset'})}
                />
            </Stack.Navigator>
        </NavigationContainer>
    );
}

