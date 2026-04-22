# Infrastructure Module: Port Forwarding

This script is designed to forward various services on port 5432 and 27017 to different services on ports 8080 and 3000, respectively. The service names are provided in the `svc` field.

## Prerequisites
- A Kubernetes cluster with a running `kubernetes` namespace.
- A service named `timescaledb`, `mongodb`, `rabbitmq`, `argocd-server`, `prometheus-stack-grafana`, and `ollama-service`.
- A service named `backend-api`.

## Usage

1. Run the script to forward services:
   ```bash
   ./port-forwarder.sh
   ```

2. Access the forwarded services:

   - TimescaleDB: http://localhost:5432
   - MongoDB: http://localhost:27017
   - RabbitMQ: http://localhost:15672

## Notes

- The script uses `kubectl` to manage the services and port forwarding.
- The service names are provided in the `svc` field, which can be customized for different environments or projects.

This module is useful for isolating and managing multiple services on a single Kubernetes cluster.