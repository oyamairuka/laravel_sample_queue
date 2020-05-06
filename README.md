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

## ビルド
ビルドにはPOCO c++ ライブラリが必要.<br>
[Poco c++](https://pocoproject.org/)

Windows10のWSL(Ubuntu)にてcmake(version 3.17.1)でビルド.
1. laravel_sample_queueプロジェクト直下のCMakeList.txtの以下の値を各環境に変更(POCO c++ ライブラリのインストール先)
```
set(Poco_INCLUDE_DIRS /usr/local/include)
set(Poco_LIBRARY_DIRS /usr/local/lib/poco)
```
2. laravel_sample_queueプロジェクト直下にて以下を実行
```
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
<br>
このCMakeList.txtにはデバッグ用やWindows用の分岐があるが未完成.<br>
<br>

laravel側は
1. laravel_sample_queueプロジェクト直下のphpディレクトリの中身をコピーする(ディレクトリ構造ごと).
2. config/app.phpのApplication Service Providersに次のプロバイダーを加える.
```
App\Providers\LSQServiceProvider::class,
```
3. config/queue.phpのconnectionsに次の記述を加える.
```
'lsq' => [
    'driver' => 'lsq',
    'host' => 'localhost',
    'port' => 8787,
    'queue' => 'default'
],
```
4. .envのQUEUE_CONNECTIONをlsqに設定する.
```
QUEUE_CONNECTION=lsq
```

## Web Api
ジョブのpush,pop以外に下記httpリクエストを受け付ける.(localhostでport8787の例)<br>
<br>
* http://localhost:8787/lsq/help -> helpテキストが返る
* http://localhost:8787/lsq/count -> 現在のキューの要素数が返る
* http://localhost:8787/lsq/list -> 現在のキューの要素一覧が返る(未実装) 
* http://localhost:8787/lsq/next -> 次に追加される要素に与えられるIDが返る

## LaravelSampleQueue.properties(設定ファイル)
```
port=8787
data.dir=${system.homeDir}/works/
data.file=elements.json

logging.channels.c1.path=${system.homeDir}/works/LaravelSampleQueue.log
```
* port -> LaravelSampleQueueがリクエストを受け付けるポート番号
* data.dir -> プロセスkill時に現在のキューの内容を出力するファイルの保存先(この例ではユーザーのホームディレクトリ内のworkディレクトリを指定)
* data.file=elements.json -> データ保存ファイル名
* logging.channels.c1.path -> ログファイル名(この例ではdata.dirと同じディレクトリにLaravelSampleQueue.logという名前で保存) 

<br>
この設定ファイルは実行ファイルと同じディレクトリかその上層のディレクトリに配置する.<br>
data.dirにはidという名前でシーケンス値が書かれたファイルも保存される.