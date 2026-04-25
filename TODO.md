# 🗺️ SolarTracker: Rozwój Architektury

## Faza 1: Ekspozycja i Infrastruktura
- [ ] **Grafana:** Dashboardy.
- [ ] **GH Actions:** Poprawa budowania obrazów żeby budowało tylko jak coś się zmieni i dodać Dockerfile dla infrastructure runnera żeby miał dockera i terraforma, oraz dla ai-agent runnera żeby miał pythona.

## Faza 3: Bezpieczeństwo i IoT
- [ ] **VPN (OpenVPN):** Postawienie serwera VPN w klastrze. Podłączenie fizycznych układów ESP32 do prywatnej sieci K8s z ominięciem publicznego Wi-Fi.

## Faza 4: Pełna Automatyzacja
- [ ] **Argo Events:** Nasłuchiwanie na webhooki (GitHub, Docker Registry) i eventy systemowe.
- [ ] **Argo Workflows:** Uruchamianie zautomatyzowanych zadań (np. budowanie nowych obrazów Dockera, backup bazy, testy E2E) po wyzwoleniu przez Argo Events.

## Faza 5: Aplikacja i Autoryzacja
- [ ] **Keycloak (Auth):** Wdrożenie serwera tożsamości (OIDC/OAuth2). Konfiguracja ról i zabezpieczenie Endpointów Backend API.
- [ ] **Mobile App:** logowanie, cache, powiadomienia, biometria

# Usefull commands:
kubectl create secret generic github-runner-creds \
  --from-literal=github-token= \
  -n infrastructure \
  --dry-run=client -o yaml > raw-secret.yml

kubeseal --cert mycert.pem --format=yaml < raw-secret.yml > infrastructure/k8s/base/github-runner/secret.yml

rm raw-secret.yml

kubectl get secret ai-agent-creds -n ai-agent -o jsonpath="{.data.github-token}" | base64 --decode ; echo