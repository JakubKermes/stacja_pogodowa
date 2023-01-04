<template>

    <div>
        <div class="_2-col just-l">Wykres:</div>
        <div class="_2-col just-r">
            <input type="button" value="1 dzien" name="time_offset" onclick='fetch("http://localhost:8000/test/?t=-1").then(response => response.text()).then(text => console.log(text));'>
            <input type="button" value="7 dni" name="time_offset" onclick='fetch("http://localhost:8000/test/?t=-7").then(response => response.text()).then(text => console.log(text));'>
            <input type="button" value="update" v-on:click="update_chart">

        </div>
    </div>
    <div>
        <canvas id="myChart" width="400" height="400"></canvas>
    </div>
</template>

<script>
import {Chart} from 'chart.js/auto';
export default {
    methods: {
        update_chart(){
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
                    Pressure.push(row.Pressure);
                    Humidity.push(row.Humidity);
                    LightLevel.push(row.Lightlevel);
                });
                if (!this.chart) {
                    const ctx = document.getElementById('myChart').getContext('2d');
                    this.chart = new Chart(ctx, {
                        type: 'line',
                        data: {
                            labels: DateTime,

                            datasets: [
                                {
                                    label: 'Temperature',
                                    data: Temperature,
                                },
                                {
                                    label: 'Pressure',
                                    data: Pressure,
                                },
                                {
                                    label: 'Humidity',
                                    data: Humidity,
                                },
                                {
                                    label: 'Light level',
                                    data: LightLevel,
                                },
                            ],
                        },

                    });
                } else {
                        // Update the chart with the new data
                        this.chart.data.labels = DateTime;
                        this.chart.data.datasets[0] = Temperature;
                        this.chart.data.datasets[1] = Pressure;
                        this.chart.data.datasets[2] = Humidity;
                        this.chart.data.datasets[3] = LightLevel;
                        this.chart.update({preservation: true});
                }
            });
    },
};
function update_chart(){
    console.log("dziala");
}
fetch("http://localhost:8000/test/?t=-1")
    .then(response => response.text())
    .then(text => console.log(text));

</script>
