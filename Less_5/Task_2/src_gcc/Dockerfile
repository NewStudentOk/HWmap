FROM ubuntu:latest
RUN apt update && apt install -y g++ mc
WORKDIR  /app
COPY ./main.cpp .
RUN g++ main.cpp -o fig_side
CMD [ "./fig_side"]
