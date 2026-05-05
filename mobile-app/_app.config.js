// app.config.js
import 'dotenv/config';

export default {
  "expo": {
    "name": "Solar Tracker",
    "slug": "solartracker",
    "version": "1.0.0",
    "scheme": "solartracker",
    "orientation": "default",
    "icon": "./assets/icon.png",
    "userInterfaceStyle": "dark",
    "newArchEnabled": true,
    "splash": {
      "image": "./assets/adaptive-icon.png",
      "resizeMode": "contain",
      "backgroundColor": "#1E1E1E"
    },
    "android": {
      "adaptiveIcon": {
        "foregroundImage": "./assets/adaptive-icon.png",
        "backgroundColor": "#1E1E1E"
      },
      "notification": {
        "icon": "./assets/icon.png",
        "color": "#1E1E1E"
      },
      "edgeToEdgeEnabled": false,
      "package": "com.ksoltysik.solartracker",
      "googleServicesFile": "./google-services.json",
      "config": {
        "googleMaps": {
          "apiKey": process.env.GOOGLE_MAPS_API_KEY
        }
      }
    },
    "plugins": [
      "expo-web-browser",
      "expo-secure-store"
    ],
    "extra": {
      "eas": {
        "projectId": "ac6ab835-dfbb-4fb8-ae6e-b4194636a481"
      }
    },
    "owner": "ksoltysik"
  }
}