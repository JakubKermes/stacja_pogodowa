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

// test amogus

<script>
import {Chart} from 'chart.js/auto';
import {shallowRef} from 'vue';
import moment from "moment";

export default {
    methods: {
        update_chart() {
            console.log("hej");
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
                // console.log(JSON.stringify(e));
                const DateTime = [];
                const Temperature = [];
                const Pressure = [];
                const Humidity = [];
                const LightLevel = [];
                e.forEach(function (row) {
                    DateTime.push(row.DateTime);
                    Temperature.push(row.Temperature);
                    Pressure.push(row.Pressure/10);
                    Humidity.push(row.Humidity);
                    LightLevel.push(row.Lightlevel);
                });

                if (!this.chart) {
                    const ctx = document.getElementById('myChart').getContext('2d');
                    this.chart = shallowRef(new Chart(ctx, {
                        type: 'line',
                        data: {
                            labels: DateTime.map(item => moment(item).format("HH:mm")),

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
                                    // x: {
                                    //     type: 'time',
                                    //     time: {
                                    //         format: 'YYYY-MM-DD HH:mm:ss',
                                    //         unit: 'hour',
                                    //         unitStepSize: 1,
                                    //         displayFormats: {
                                    //             hour: 'HH:mm',
                                    //         }
                                    //     }
                                    // },
                                    xAxes: [{
                                        type: 'time',
                                        time: {
                                            parser: 'YYYY-MM-DD HH:mm:ss',
                                        },
                                        ticks: {
                                            min: 0,
                                            max: 100,
                                            stepSize: 10,
                                        }
                                    }],
                                }
                            }
                        },
                    }))
                } else {
                    console.log("update");
                    this.chart.data.labels = DateTime;
                    this.chart.data.datasets[0].data = Temperature;
                    this.chart.data.datasets[1].data = Pressure;
                    this.chart.data.datasets[2].data = Humidity;
                    this.chart.data.datasets[3].data = LightLevel;
                    this.chart.update();
                    console.log(this.chart.data)
                }
            });
    },
};


fetch("http://localhost:8000/test/?t=-2")
    .then(response => response.text())
    .then(text => console.log(text));

</script>
