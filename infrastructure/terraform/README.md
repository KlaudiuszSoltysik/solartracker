# Infrastructure Configuration

This Terraform configuration is designed to manage a Cloudflare tunnel and its associated resources. The `cloudflare_tunnel` resource is used to define the tunnel's configuration, while the `cloudflare_record` resource manages DNS records for the tunnel.

## Variables

- **cloudflare_api_token**: This variable holds the API token obtained from Cloudflare.
- **cloudflare_account_id**: This variable stores the ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: This variable specifies the zone ID where the tunnel is located.
- **tunnel_secret**: This variable contains the secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id = var.cloudflare_zone_id
  name    = "api"
  value   = "${cloudflare_tunnel.api_tunnel.id}.cfargotunnel.com"
  type    = "CNAME"
  proxied = true
}
```

- **zone_id**: The ID of the zone where the tunnel is located.
- **name**: The DNS record name for the tunnel.
- **value**: The value associated with the DNS record.
- **type**: The type of DNS record (e.g., CNAME).
- **proxied**: A boolean indicating whether the DNS records should be proxied.

## Terraform Variables

```markdown
variable "cloudflare_api_token" { type = string }
variable "cloudflare_account_id" { type = string }
variable "cloudflare_zone_id" { type = string }
variable "tunnel_secret" { type = string }

```

- **cloudflare_api_token**: The API token obtained from Cloudflare.
- **cloudflare_account_id**: The ID of the Cloudflare account that owns the tunnel.
- **cloudflare_zone_id**: The zone ID where the tunnel is located.
- **tunnel_secret**: The secret used to authenticate with Cloudflare.

## Terraform Configuration

```markdown
terraform {
  backend "kubernetes" {
    secret_suffix = "cloudflare-tfstate"
    namespace     = "infrastructure"
  }
  required_providers {
    cloudflare = {
      source  = "cloudflare/cloudflare"
      version = "~> 4.0"
    }
    kubernetes = {
      source  = "hashicorp/kubernetes"
      version = "~> 2.0"
    }
  }
}

provider "cloudflare" {
  api_token = var.cloudflare_api_token
}
```

## Terraform Resources

- **cloudflare_tunnel**: Defines the Cloudflare tunnel configuration.
- **cloudflare_record**: Manages DNS records for the tunnel.

### cloudflare_tunnel

```markdown
resource "cloudflare_tunnel" "api_tunnel" {
  account_id = var.cloudflare_account_id
  name       = "solartracker-api-tunnel"
  secret     = var.tunnel_secret
}
```

- **account_id**: The ID of the Cloudflare account that owns the tunnel.
- **name**: The name of the tunnel.
- **secret**: The secret used to authenticate with Cloudflare.

### cloudflare_record

```markdown
resource "cloudflare_record" "api_dns" {
  zone_id =