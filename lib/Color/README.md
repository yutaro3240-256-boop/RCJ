# Color ライブラリ

カラーセンサS9706用自作ライブラリです。センサを登録し、赤・緑・青（RGB）の値を読み取ったり、指定した色に近いかを調べたりできます。

## 基本的な使い方

```cpp
#include <Color.h>

Color colorSensor;

void setup() {
  // gate, ck, range, dout の順にピン番号を指定してセンサを登録します。
  colorSensor.begin(2, 3, 4, 5);
}

void loop() {
  // 第2引数 true は、値を取得する前に新しく読み取るという意味です。
  RGB rgb = colorSensor.get(0, true);

  // rgb.r、rgb.g、rgb.b に赤・緑・青の読み取り値が入ります。
}
```

センサは `begin()` を呼んだ順に登録され、最初のセンサの番号は `0` です。登録できる数は最大 `maxsensors` 個（初期値は `4`）です。
登録するセンサの数を増やしたい場合、`#include <Color.h>`の前に`#define maxsensors N`(`N`は登録したいセンサの数)を定義してください．
`RGB` の各値は `uint16_t` 型です。

## センサの設定と登録解除

### `begin(gate, ck, range, dout)`

センサを登録して、各ピンを入出力用に設定します。このライブラリでセンサを使いたい場合、setup関数内でこれを使うことが前提になります。`gate`、`ck`、`range`、`dout` の順にピン番号を渡します。

- 成功すると `true`、登録上限に達している場合や測定中の場合は `false` を返します。
- センサの番号は登録した順に `0`、`1`、…となります。

### `erase(ID = 0)`

指定した番号のセンサを登録から外します。後ろに登録されていたセンサの番号は前に詰まります。成功すると `true`、番号が無効または測定中の場合は `false` を返します。

### `eraseall()`

登録されているセンサをすべて登録解除します。1つ以上を解除できた場合は `true` を返します。センサが登録されていない場合や測定中の場合は `false` です。

### `sensorCount()`

現在登録されているセンサの数を `uint8_t` で返します。

### `setIntegrationTime(t)`

センサが光を取り込む時間をミリ秒で指定します。初期値は `50` ミリ秒です。測定中に呼び出しても設定は変わりません。

## 値の読み取り

### `read(ID = 0)`

指定したセンサを1回読み取ります。正常に読み取りを開始できた場合は `true`、番号が無効または別の測定中の場合は `false` を返します。読み取った値はライブラリ内に保存されます。

### `read_average(count, ID = 0)`

指定したセンサを `count` 回読み取り、各色の平均値を保存します。成功すると `true` を返します。`count` が `0` 以下、番号が無効、または別の測定中の場合は `false` です。

### `readall()`

登録されているすべてのセンサを1回ずつ読み取ります。結果は各センサに保存されます。

### `read_averageall(count)`

登録されているすべてのセンサをそれぞれ `count` 回読み取り、平均値を保存します。`count` が `0` 以下の場合は何もしません。

### `get(ID = 0, read = false)`

保存されている値を `RGB` として返します。`read` を `true` にすると、値を返す前にセンサを読み取ります。番号が無効の場合は、赤・緑・青がすべて `0` の `RGB` を返します。

```cpp
RGB rgb = colorSensor.get(0);       // 保存済みの値を取得
RGB fresh = colorSensor.get(0, true); // 読み取ってから取得
```

### `get_average(count, ID = 0)`

指定したセンサを `count` 回読み取って平均値を求め、その値を `RGB` で返します。番号が無効の場合は、すべて `0` の `RGB` を返します。

### `getall(rgb[], read = false)`

登録されている全センサの値を、渡した `RGB` 配列に入れます。配列には `sensorCount()` 個以上の要素が必要です。`read` を `true` にすると、各センサの値を取得するたびに読み取ります。

### `get_averageall(count, rgb[])`

すべてのセンサについて `count` 回読み取った平均値を求め、配列に入れます。配列には `sensorCount()` 個以上の要素が必要です。

### `out(R, G, B, ID = 0, read = false)`

赤・緑・青の値を、それぞれ整数の変数に入れます。成功すると `true`、番号が無効の場合は `false` です。`read` を `true` にすると、値を入れる前に読み取ります。

```cpp
int r, g, b;
if (colorSensor.out(r, g, b, 0, true)) {
  // r、g、b に読み取り値が入っています。
}
```

### `getBrightness(ID = 0, read = false)`

赤・緑・青の値を足した明るさの目安を `uint16_t` で返します。`read` が `true` なら、計算前に読み取ります。番号が無効の場合は `0` を返します。

## 色の比率と色比較

### `out_ratio(R, G, B, ID = 0, read = false)`

各色がRGB合計に占める割合を、合計が `100` になる数値として整数の変数に入れます。たとえば赤が合計の半分なら、赤の値はおよそ `50` です。成功すると `true` を返します。番号が無効、またはRGBの合計が `0` の場合は `false` です。`read` が `true` なら、割合を計算する前に読み取ります。

### `setcompareRange(range)`

`compare()` で色を比べるときの許容幅を設定します。比較する各色について、指定した値から上下に `range` 以内なら一致とみなします。初期値は `20` です。

### `compare(R, G, B, ID = 0, read = false)`

指定したセンサのRGB値が、渡したRGB値に近いかを調べます。赤・緑・青のすべてが許容幅内なら `true`、それ以外は `false` です。`read` が `true` なら、比較前に読み取ります。

### `setcompareRange_ratio(range)`

`compare_ratio()` で割合を比べるときの許容幅を設定します。各色の割合が指定値から上下に `range` 以内なら一致とみなします。初期値は `10` です。

### `compare_ratio(R, G, B, ID = 0, read = false)`

指定したセンサのRGB割合が、渡した割合に近いかを調べます。3色すべてが許容幅内なら `true` を返します。`read` が `true` なら、比較前に読み取ります。

### `getcompare(rgb, ID = 0, read = false)`

`RGB` 型で渡した値を使って色を比較します。`compare(rgb.r, rgb.g, rgb.b, ID, read)` と同じ結果を返します。

## 複数センサの非同期読み取り

複数のセンサの読み取りを、待ち時間中にほかの処理を進めながら行えます。読み取り完了までの間、`update()` を繰り返し呼び出してください。

### `startall()`

すべてのセンサの読み取りを開始します。開始できると `true` を返します。すでに別の読み取り中の場合は `false` です。

### `update()`

`startall()` の後、繰り返し呼び出して読み取りの進み具合を更新します。設定された積分時間が過ぎると、読み取り完了状態になります。

### `available()`

読み取りが完了して結果を受け取れる状態なら `true`、まだなら `false` を返します。

### `finishall()`

読み取り完了後に、すべてのセンサの値を取得して保存します。完了状態で実行できた場合は `true` を返し、読み取り中または開始前の場合は `false` です。

```cpp
void loop() {
  if (colorSensor.startall()) {
    while (!colorSensor.available()) {
      colorSensor.update();
      // この間に別の処理を行うこともできます。
    }
    colorSensor.finishall();
    RGB firstSensor = colorSensor.get(0);
  }
}
```

## 引数のまとめ

- `ID`: センサ番号。登録順に `0` から始まります。
- `count`: 平均を求める読み取り回数。`1` 以上を指定します。
- `read`（または `_read`）: `true` にすると、値の取得・比較の前に読み取ります。初期値は `false` です。
- `R`, `G`, `B`: 比較するRGB値、または結果を受け取る整数変数です。割合の関数では、RGB合計を `100` とした値を使います。