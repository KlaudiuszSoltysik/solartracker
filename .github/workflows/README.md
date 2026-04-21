# Build and Push Docker Images

This workflow builds and pushes Docker images to a specified repository based on the `build-and-push.yml` file.

## Files Content

- **.github/workflows/build-and-push.yml**:
  - **on**: 
    - push: branches: "master"
      paths: 
        - 'services/**'
        - 'cron-jobs/**'
        - '.github/workflows/**'

  - **permissions**: 
    - packages: write
    - contents: read

- **jobs**: 
  - **build-and-push**: 
    - **runs-on**: ubuntu-latest
      - **strategy**: 
        - matrix:
            include:
              - name: backend-api
                path: services/backend-api
              - name: telemetry-processor
                path: services/telemetry-processor
              - name: esp32-simulator
                path: services/esp32-simulator
              - name: solar-forecast
                path: cron-jobs/solar-forecast

  - **build-and-push**: 
    - **steps**:
      - **name**: Check out the repo
        - uses: actions/checkout@v4

      - **name**: Log in to the Container registry
        - uses: docker/login-action@v3
          with:
            registry: ghcr.io
            username: ${{ github.actor }}
            password: ${{ secrets.GITHUB_TOKEN }}

      - **name**: Extract metadata (tags, labels) for Docker
        - id: meta
          uses: docker/metadata-action@v5
          with:
            images: ghcr.io/klaudiuszsoltysik/solartracker/${{ matrix.name }}
            tags: |
              type=sha,format=short
              type=ref,event=branch

      - **name**: Build and push Docker image
        - uses: docker/build-push-action@v5
          with:
            context: ./${{ matrix.path }}
            push: true
            tags: ${{ steps.meta.outputs.tags }}
            labels: ${{ steps.meta.outputs.labels }}