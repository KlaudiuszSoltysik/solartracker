# 🗺️ SolarTracker: Rozwój Architektury

- [ ] **GH Actions:** Poprawa budowania obrazów żeby budowało tylko jak coś się zmieni i dodać Dockerfile dla infrastructure runnera żeby miał dockera i terraforma, oraz dla ai-agent runnera żeby miał pythona.
- [ ] **VPN (OpenVPN):** Postawienie serwera VPN w klastrze. Podłączenie fizycznych układów ESP32 do prywatnej sieci K8s z ominięciem publicznego Wi-Fi, albo wystawienie rabbita na zewnątrz i zabezpieczenie go.
- [ ] **Argo Events:** Nasłuchiwanie na webhooki (GitHub, Docker Registry) i eventy systemowe.
- [ ] **Argo Workflows:** Uruchamianie zautomatyzowanych zadań (np. budowanie nowych obrazów Dockera, backup bazy, testy E2E) po wyzwoleniu przez Argo Events.
- [ ] **Mobile App:** manual mode, api tylko dla zalogowanych, powiadomienie zjebane, nie wylogowuje się przy wylogowywaniu, logowanie nie tworzy sesji

# Usefull commands:

kubectl create secret generic expo-app-creds \
 --from-literal=expo-push-token="" \
 -n default \
 --dry-run=client -o yaml > raw-secret.yml

kubeseal --cert mycert.pem --format=yaml < raw-secret.yml > infrastructure/k8s/dev/downtime-checking/secret.yml

rm raw-secret.yml

kubectl get secret ai-agent-creds -n ai-agent -o jsonpath="{.data.github-token}" | dev64 --decode ; echo

kubectl apply -f infrastructure/k8s/dev/observability/prometheus-app.yml -n argocd