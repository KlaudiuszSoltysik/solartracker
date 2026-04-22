resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}

resource "cloudflare_tunnel_config" "api_config" {
  account_id = var.cloudflare_account_id
  tunnel_id  = cloudflare_tunnel.api_tunnel.id

  config {
    ingress_rule {
      hostname = "api.260824.xyz"
      service  = "http://backend-api.services.svc.cluster.local:8000"
    }
    ingress_rule {
      service = "http_status:404"
    }
  }
}

resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}

resource "kubernetes_secret" "cloudflared_token" {
  metadata {
    name      = "cloudflared-creds"
    namespace = "infrastructure"
  }
  data = {
    cloudflared-token = cloudflare_tunnel.api_tunnel.tunnel_token
  }
  type = "Opaque"
}