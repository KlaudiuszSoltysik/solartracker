# 🗺️ SolarTracker: Rozwój Architektury

- [ ] **VPN (OpenVPN):** Postawienie serwera VPN w klastrze. Podłączenie fizycznych układów ESP32 do prywatnej sieci K8s z ominięciem publicznego Wi-Fi, albo wystawienie rabbita na zewnątrz i zabezpieczenie go.
- [ ] **Mobile App:** manual mode

# Usefull commands:

kubectl create secret generic keycloak-creds \
 --from-literal=admin-password="admin" \
 --from-literal=password="admin" \
 --from-literal=postgres-password="admin" \
 -n default \
 --dry-run=client -o yaml > raw-secret.yml

kubeseal --cert mycert.pem --format=yaml < raw-secret.yml > infrastructure/k8s/dev/keycloak/secret-default.yml

rm raw-secret.yml

kubectl get secret ai-agent-creds -n ai-agent -o jsonpath="{.data.github-token}" | base64 --decode ; echo

kubectl apply -f infrastructure/k8s/dev/observability/prometheus-app.yml -n argocd