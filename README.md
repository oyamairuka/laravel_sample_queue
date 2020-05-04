# laravel_sample_queue
<br>
LaravelのQueueとして利用できるプログラム.<br>
LaravelのQueueの仕組みの理解のために作った個人的な練習.<br>
現状では通常のdispatchとdelayの実行までは確認.<br>

例:
```php:title
LSQTestJob::dispatch(new DateTime());
LSQTestJob::dispatch(new DateTime())->delay(now()->addMinutes(1));
```

ビルドにはPOCO c++ ライブラリが必要.<br>
[Poco c++](https://pocoproject.org/)

php側ソースは徐々に追加予定.<br>
ジョブのpush,pop以外に下記httpリクエストを受け付ける.(localhostでport8787の例)<br>
<br>
* http://localhost:8787/lsq/help -> helpテキストが返る
* http://localhost:8787/lsq/count -> 現在のキューの要素数が返る
* http://localhost:8787/lsq/list -> 現在のキューの要素一覧が返る(未実装) 
* http://localhost:8787/lsq/next -> 次に追加される要素に与えられるIDが返る
