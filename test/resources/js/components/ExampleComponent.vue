<script>
 let test = "";
export default {
    mounted() {
        Echo.channel('test')
            .listen('test', (e)=> {
                test = e;
                document.getElementById("test").innerHTML = JSON.stringify(e);
            })
        console.log('Component mounted.');

    }
}
</script>

<template>
    <div>payload: <span id="test"></span></div>
</template>
