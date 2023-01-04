@extends('layouts.app')


@section('content')
<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-8">
            <div class="card">
                <div class="card-header">{{ __('Dashboard') }}</div>

                <div class="card-body">
                    <example-component />
                </div>
            </div>
        </div>
    </div>
</div>
@endsection
<script src="transpiled-code.js">
    import ExampleComponent from "@/components/ExampleComponent.vue";
    export default {
        components: {ExampleComponent}
    }
</script>
