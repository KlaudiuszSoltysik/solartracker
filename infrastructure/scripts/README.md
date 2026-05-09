# Infrastructure Port Forwarding Script

This script is designed to forward various services on port 5432 and 27017 to different external services. It uses Kubernetes' `kubectl` command-line tool to perform the port forwarding.

## Prerequisites

- A running Kubernetes cluster with access to the specified services.
- The necessary permissions for accessing the services.

## Usage

1. Ensure that the services are running on the specified ports (5432 and 27017).
2. Run the script using `./port-forwarder.sh`.

## Output

The script will forward the specified services to external services, such as TimescaleDB, MongoDB, RabbitMQ, ArgoCD, Prometheus, Grafana, Ollama, and Backend API.

## Example Usage

- To forward TimescaleDB to a different service (e.g., `timescaledb.example.com`), use: `kubectl port-forward svc/timescaledb 5432:5432`
- To forward MongoDB to another external service (e.g., `mongodb.example.com`), use: `kubectl port-forward svc/mongodb 27017:27017`

## Notes

- The script uses `kubectl` commands to perform the port forwarding.
- It assumes that the services are running on the specified ports and have access to the external services.

This script is intended for internal developers who need to automate the process of forward port forwarding.