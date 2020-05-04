# laravel_sample_queue
<br>
LaravelのQueueとして利用できるプログラム.<br>
LaravelのQueueの仕組みの理解のために作った個人的な練習.<br>
現状では通常のdispatchとdelayの実行までは確認.<br>

例:
```
LSQTestJob::dispatch(new DateTime());
LSQTestJob::dispatch(new DateTime())->delay(now()->addMinutes(1));
```

ビルドにはPOCO c++ ライブラリが必要.<br>
[Poco c++](https://pocoproject.org/)
<br>
Windows10のWSL(Ubuntu)にてcmake(version 3.17.1)でビルド.
1. プロジェクト直下のCMakeList.txtの以下の値を各環境に変更
```
set(Poco_INCLUDE_DIRS /usr/local/include)
set(Poco_LIBRARY_DIRS /usr/local/lib/poco)
```
2. プロジェクト直下にて以下を実行
```
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
<br>
このCMakeList.txtにはデバッグ用やWindows用の分岐があるが未完成.<br>

php側ソースは徐々に追加予定.<br>
ジョブのpush,pop以外に下記httpリクエストを受け付ける.(localhostでport8787の例)<br>
<br>
* http://localhost:8787/lsq/help -> helpテキストが返る
* http://localhost:8787/lsq/count -> 現在のキューの要素数が返る
* http://localhost:8787/lsq/list -> 現在のキューの要素一覧が返る(未実装) 
* http://localhost:8787/lsq/next -> 次に追加される要素に与えられるIDが返る
