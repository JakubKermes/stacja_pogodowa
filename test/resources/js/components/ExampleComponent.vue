<template>
    <div>
        <canvas id="myChart" width="400" height="400"></canvas>
    </div>
    <div class="cnt">
        <input type="button" value="1 dzien" name="time_offset"
               onclick='fetch("http://localhost:8000/test/?t=-1").then(response => response.text()).then(text => console.log(text));'>
        <input type="button" value="7 dni" name="time_offset"
               onclick='fetch("http://localhost:8000/test/?t=-7").then(response => response.text()).then(text => console.log(text));'>
        <input type="button" value="update" v-on:click="update_chart">
    </div>
</template>

<script>
import {Chart} from 'chart.js/auto';
import {shallowRef} from 'vue';
import moment from "moment";

export default {

    methods: {
        update_chart() {
            this.chart.update();
        }
    },
    data() {
        return {
            chart: null,
        };
    },
    mounted() {
        Echo.channel('test')
            .listen('test', (e) => {
                const DateTime = [];
                const Temperature = [];
                const Pressure = [];
                const Humidity = [];
                const LightLevel = [];
                let dateFormat= "YYYY-MM-DD HH:mm:ss";
                let countData = 0;

                e.forEach(function (row) {
                    countData++;
                    DateTime.push(row.DateTime);
                    Temperature.push(row.Temperature);
                    Pressure.push(row.Pressure/10);
                    Humidity.push(row.Humidity);
                    LightLevel.push(row.Lightlevel);
                });

                if (countData > 250){
                    dateFormat = "MM-DD HH:mm";
                }
                else{
                    dateFormat = "HH:mm";
                }

                if (!this.chart) {
                    const ctx = document.getElementById('myChart').getContext('2d');
                    this.chart = shallowRef(new Chart(ctx, {
                        type: 'line',
                        data: {
                            labels: DateTime.map(item => moment(item).format(dateFormat)),

                            datasets: [
                                {
                                    label: 'Temperature [°C]',
                                    data: Temperature,
                                },
                                {
                                    label: 'Pressure [kPa]',
                                    data: Pressure,
                                },
                                {
                                    label: 'Humidity [%]',
                                    data: Humidity,
                                },
                                {
                                    label: 'Light level [%]',
                                    data: LightLevel,
                                },
                            ],
                            options: {
                                scales: {
                                    y: {
                                        beginAtZero: true,
                                    },
                                    x: {
                                    },
                                }
                            }
                        },
                    }))
                } else {
                    this.chart.data.labels = DateTime.map(item => moment(item).format(dateFormat));
                    this.chart.data.datasets[0].data = Temperature;
                    this.chart.data.datasets[1].data = Pressure;
                    this.chart.data.datasets[2].data = Humidity;
                    this.chart.data.datasets[3].data = LightLevel;
                    this.chart.update();
                }
            });
    },
};

fetch("http://localhost:8000/test/?t=-2")
    .then(response => response.text())
    .then(text => console.log(text));

</script>
