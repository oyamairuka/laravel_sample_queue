<!DOCTYPE html>
<html lang="{{ str_replace('_', '-', app()->getLocale()) }}">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="csrf-token" content="{{ csrf_token() }}">

    <title>laravel sample queue test</title>

    <link href="css/skeleton.css" rel="stylesheet">
    <script src="js/umbrella.min.js"></script>
</head>

<body>
    <h3>
        Laravel Sample Queue テスト
    </h3>
    <button id="addButton" class="button-primary">テストジョブ追加</button>
    <button id="addLaterButton" class="button-primary">遅延実行追加</button>
</body>
<script>
    u(document.getElementById('addButton')).handle('click', async e => {
        const body = '';
        const data = await fetch('/lsqtest/add', {
            method: 'POST',
            headers: {
                'X-CSRF-TOKEN': u('meta[name="csrf-token"]').attr('content')
            },
            body: body
        });
        console.log('Response data:', data);
    });
    u(document.getElementById('addLaterButton')).handle('click', async e => {
        const body = '';
        const data = await fetch('/lsqtest/addlater', {
            method: 'POST',
            headers: {
                'X-CSRF-TOKEN': u('meta[name="csrf-token"]').attr('content')
            },
            body: body
        });
        console.log('Response data:', data);
    });
</script>

</html>