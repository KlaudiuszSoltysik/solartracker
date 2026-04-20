#!/bin/bash

echo "🔌 Port-Forwarding..."
echo "========================================================"

cleanup() {
    kill $(jobs -p) 2>/dev/null
    wait $(jobs -p) 2>/dev/null
    exit 0
}

trap cleanup SIGINT SIGTERM

kubectl port-forward svc/timescaledb 5432:5432 > /dev/null 2>&1 &
echo "🐘 TimescaleDB:     http://localhost:5432"

kubectl port-forward svc/mongodb 27017:27017 > /dev/null 2>&1 &
echo "🍃 MongoDB:         http://localhost:27017"

kubectl port-forward svc/rabbitmq 15672:15672 5672:5672 > /dev/null 2>&1 &
echo "🐰 RabbitMQ:        http://localhost:15672"

kubectl port-forward svc/argocd-server -n argocd 8080:443 > /dev/null 2>&1 &
echo "🦑 ArgoCD:          http://localhost:8080"

kubectl port-forward svc/prometheus-stack-grafana -n observability 3000:80 > /dev/null 2>&1 &
echo "📊 Grafana:         http://localhost:3000"

kubectl port-forward svc/backend-api 8000:8000 > /dev/null 2>&1 &
echo "⚙️ Backend API:     http://localhost:8000/docs"

echo "========================================================"

wait
