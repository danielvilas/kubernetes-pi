FROM arm32v7/debian:stable-slim
LABEL MAINTAINER="Daniel Vilas"
LABEL DESCRIPTION="UPS-HAT monitoring image for Kubernetes"

ADD ups-hat-influx /usr/bin/ups-hat-influx

CMD [ "/usr/bin/ups-hat-influx", "-c", "-v"]