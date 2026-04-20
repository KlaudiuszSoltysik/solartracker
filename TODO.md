- argo workflows
- argo events
- tests
- terraform
- vpn?
- cloudflare
- resources
- prod enviorment + dev edit
- keycloak
- mobile app

# Usefull commands:
kubectl create secret generic grafana-creds \
  --from-literal=username=admin \
  --from-literal=password=admin \
  -n observability \
  --dry-run=client -o yaml > raw-secret.yml

kubeseal --cert mycert.pem --format=yaml < raw-secret.yml > infrastructure/k8s/base/observability/secret.yml

rm raw-secret.yml