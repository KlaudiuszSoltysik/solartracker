# 🗺️ SolarTracker: Rozwój Architektury

## Faza 1: Ekspozycja i Infrastruktura (IaC)
- [ ] **Cloudflare Tunnel + Ingress:** Wystawienie API i usług (Grafana/Argo) na zewnątrz bez otwierania portów na routerze. Podpięcie własnej domeny.
- [ ] **Terraform:** Zakodowanie konfiguracji klastra (węzły) i Cloudflare Tunneli jako Infrastructure as Code.

## Faza 2: Optymalizacja K8s (Zasoby)
- [ ] **Resource Limits & Requests:** Konfiguracja limitów CPU i RAM dla każdego namespace'u (zapobieganie OOMKillom i zagłodzeniu usług).
- [ ] **GPU Node Affinity:** Wydzielenie osobnego węzła (Node) dla ciężkich zadań AI. Ustawienie `nodeSelector` i `tolerations` dla Agenta.

## Faza 3: Bezpieczeństwo i IoT
- [ ] **VPN (WireGuard):** Postawienie serwera VPN w klastrze. Podłączenie fizycznych układów ESP32 do prywatnej sieci K8s z ominięciem publicznego Wi-Fi.

## Faza 4: Pełna Automatyzacja (GitOps + Event-Driven)
- [ ] **Argo Events:** Nasłuchiwanie na webhooki (GitHub, Docker Registry) i eventy systemowe.
- [ ] **Argo Workflows:** Uruchamianie zautomatyzowanych zadań (np. budowanie nowych obrazów Dockera, backup bazy, testy E2E) po wyzwoleniu przez Argo Events.

## Faza 5: Aplikacja i Autoryzacja
- [ ] **Keycloak (Auth):** Wdrożenie serwera tożsamości (OIDC/OAuth2). Konfiguracja ról i zabezpieczenie Endpointów Backend API. (Celowo jako overengineering do nauki).
- [ ] **Mobile App:** Napisanie aplikacji klienckiej konsumującej API. Integracja logowania przez Keycloak.

# Usefull commands:
kubectl create secret generic ai-agent-creds \
  --from-literal=github-token=token \
  -n ai-agent \
  --dry-run=client -o yaml > raw-secret.yml

kubeseal --cert mycert.pem --format=yaml < raw-secret.yml > infrastructure/k8s/base/ai-agent/secret.yml

rm raw-secret.yml