# gb-studio-xv-plugins
GB Studio 4 用のプラグイン集

## 概要
GB Studio で開発中のゲーム「XV」の副産物です。現行バージョン（4.0.1）のイベントでは実現できない機能をプラグインとして実装しています。

クセの強いプラグイン集なので万人向けではないかもしれませんが、役に立つ人もいるかもしれません。
商用・非商用問わずご自由にお使いください。ただし、これらのプラグイン集は実験的な制作物なので、将来予告なく改変・削除する可能性があります。また、バグや追加機能の追加は著者自身が必要としない場合は原則いたしませんので、利用はくれぐれも自己責任でお願いします。

クレジット記載などは不要ですが、クレジットいただける場合はこちらをお使いください：Tomo@indiegdevstdio または Tomo。

## 内容
- Array_Factory `[仮想配列操作用プラグイン集]`
  - Array_Manager_Set `[複数のグローバル変数を統合させて配列として扱う（配列への値を代入）]`
  - Array_Manager_Get `[複数のグローバル変数を統合させて配列として扱う（配列からの値を取得）]`
- Obstacle_Checker `[衝突判定用プラグイン集]`
  - Actor_Walkability_Checker `[アクターの進行方向の障害物を取得する]`
  - Obstacle_Checker `[タイルの障害物の情報を取得する]`
- Sprite_Tile_Replacer `[指定のスプライトタイルを置き換える（VRAM バンク切り替え可能）]`

---

## 導入

本プラグイン リポジトリの [Code] > [Download ZIP] からプラグインをダウンロード・解凍します。

![download_from_github](https://github.com/user-attachments/assets/6e3d38ac-03a1-4402-ac57-90d59e8e522b)


GB Studio プロジェクトフォルダの「plugins」フォルダに jaJP の中にあるフォルダをコピーしてください。

※ assets フォルダの中ではなく、プロジェクトフォルダ直下であることに注意してください。

![plugin_install](https://github.com/user-attachments/assets/1f991de8-b7b3-42e1-b0b8-8fab141a18c7)

[イベントの追加] ダイアログの [XV プラグイン] カテゴリ サブメニューから使用するイベントを追加します。

![adding_plugin_events](https://github.com/user-attachments/assets/efd9f8f9-25b7-4d8b-b14e-651dd1d53da4 "イベントの追加")
![add_events_sample](https://github.com/user-attachments/assets/818cf8a2-8d61-4acd-a7c7-df8bf8de87e6)


---

## 説明

***Array_Factory*** `[仮想配列操作用プラグイン集]`

- Array_Manager_Set `[複数のグローバル変数を統合させて配列として扱う（配列への値を代入）]`

  最大 16 個のグローバル変数を統合して 1 次元配列のように扱うことができます。さらに個々のグローバル変数を、指定したビット数に分割することで、格納できる値の最大値を犠牲にする代わりに、より多くの配列を扱えるようになります。この分割設定は [各配列要素のビットサイズ] プロパティで指定できます。分割した場合の配列の要素数の上限は次の通りです。<1 ビット> = 256、<2 ビット> = 128、<4 ビット> = 64、<8 ビット> = 32、<16 ビット> = 16。

  ![array_manager_set_event](https://github.com/user-attachments/assets/b342fadc-9f76-4da7-bda9-4d02363977aa)


  <dl>
  <dt>グローバル変数 1 〜 16</dt>
  <dd>
    統合したいグローバル変数を指定します。
    統合したグローバル変数は、ひとつの「仮想グローバル変数」として扱うことができます。仮想グローバル変数にはインデックス（配列番号）が割り当てられるので、例えば統合前のグローバル変数 3 にアクセスしたい場合は、<仮想グローバル変数[2]> のようなイメージでアクセスすることができます（注：配列番号は 0 から始まります）。


    ![array_manager_virtual_array_concept](https://github.com/user-attachments/assets/383fdd0a-0a6a-47fc-81c5-0edaea915d34)
  </dd>
  <dt>使用するグローバル変数の数</dt>
  <dd>
    上記で設定した変数のうち、冒頭から数えていくつのグローバル変数を統合対象にするかを指定します。上記のスクショの例では、2 と指定した場合、グローバル変数 1 とグローバル変数 2 のみを統合し、他のグローバル変数が指定されていても無視されます。デフォルトの 16 を指定すると、すべてのグローバル変数が統合されます。
  </dd>
  <dt>各配列要素のビットサイズ</dt>
  <dd>より多くの配列を扱えるように、1 つのグローバル変数を何ビットで分割するかを指定します（GB Studio の各グローバル変数は 16 ビットのビット数を持ちます）。例えば、「2」を指定すると、各グローバル変数が 8 分割されます（例：1 つのグローバル変数は 16 ビットなので、8 個の 2 ビット値を持つ変数に分割することができます）。「8」を指定すると、2 個の要素（各要素は 8 ビットの値を持つ）に分割されます。


  ![Array_Manager_bit_divide](https://github.com/user-attachments/assets/7e0653d0-850a-4b1c-82e5-3522f780d437)

  [各配列要素のビットサイズ] で変数を分割した場合、8 ビットと 16 ビットで分割した場合のみ、マイナス値が使用できます。また、分割した場合に使用できる各変数（配列要素）の最小・最大値は次の通りです。<1 ビット> = 0〜1、<2 ビット> = 0〜3、<4 ビット> = 0〜15、<8 ビット> = -128〜127、<16 ビット> = -32,768〜32,767。
  </dd>
  <dt>配列インデックス</dt>
  <dd>上記で分割されたグローバル変数を 1 つのまとまりとした時に、値を設定したいインデックスを指定します。例えば、16 個のグローバル変数を指定し、それぞれ 1 ビットで分割した場合は、0〜255 の範囲のインデックスを指定することができます。</dd>
  <dt>設定値</dt>
  <dd>指定した配列インデックスの要素に設定する値（整数または変数）を指定します。</dd>
  </dl>

  **グローバル変数を 16 個統合した場合の例**

  | 各配列要素のビットサイズ | 最大要素数（配列サイズ） | 最小〜最大値 |
  |:-----------|:------------:|:------------:|
  | 1 | 256 |0〜1|
  | 2 | 128 |0〜3|
  | 4 | 64 |0〜15|
  | 8 | 32 |-128〜127|
  | 16 | 16 |-32,768〜32,767|

---

- Array_Manager_Get `[複数のグローバル変数を統合させて配列として扱う（配列からの値を取得）]`

  Array_Manager_Set プラグインで仮想グローバル変数の各配列要素に代入した値を取得します。
  
  ![array_manager_get_event](https://github.com/user-attachments/assets/6ebf6446-8883-403b-a2e2-b6f3e4a67cb8)

  <dl>
  <dt>グローバル変数 1 〜 16</dt>
  <dd>統合したいグローバル変数を指定します。これは、Array_Manager_Set で指定したグローバル変数と同じにする必要があります。</dd>
  <dt>使用するグローバル変数の数</dt>
  <dd>上記で設定した変数のうち、冒頭から数えていくつのグローバル変数を統合対象にするかを指定します。基本的には Array_Manager_Set で指定したグローバル変数と同じ値にする必要があります。</dd>
  <dt>各配列要素のビットサイズ</dt>
  <dd>1 つのグローバル変数を何ビットで分割するかを指定します。基本的には Array_Manager_Set で指定したグローバル変数と同じ値にする必要があります。</dd>
  <dt>配列インデックス</dt>
  <dd>値を取得したい配列のインデックスを指定します。詳細については、Array_Manager_Set の説明をご確認ください。</dd>
  <dt>取得した値を保存する変数</dt>
  <dd>指定した配列インデックスの要素の値を格納する変数を指定します。</dd>
  </dl>

  ___
  **（GB Studio v4.0.1）カスタムイベントとして扱う場合の注意点**

  GBS 4.0.1 のカスタムスクリプトは変数の参照渡しにバグがあるようなので、値を指定した変数（参照渡しとして）に代入されないことがあります。
  この場合、回避策として同カスタムイベントのスクリプト内に、参照渡しではないダミー変数を用意して、ダミー変数の中に一度プラグインからの返り値を入れます。その後、実際に値を代入したい参照渡しとして指定した変数にダミー変数から改めて代入します。

  （例）


  ![gbs401_cs_reference_issue_workaround](https://github.com/user-attachments/assets/faa52519-e743-44dd-9486-0fc3ed317b7c)

  
---
***Obstacle_Checker*** `[衝突判定用プラグイン集]`

- Actor_Walkability_Checker `[アクターの進行方向の障害物を取得する]`

  アクターの現在地と向きを基準にして、向かう方角に障害物が無く通行可能かどうかをチェックします。アクターが向いている方向にアクターがどのくらいのタイル数を進むかをオフセット値として指定し、アクターの現在位置から目的地の間に他のアクターが存在せず、かつコリジョンが無い場合は、障害物無しとみなされます。それ以外の場合は、衝突したオブジェクト（他のアクターまたはコリジョンが適用されたタイル）の ID 情報が代入されます。（例）変数に入る値 --> 障害物なし=0、障害物あり=コリジョン ID、またはマイナス値で表されたアクターの ID（ただし、プレイヤーの ID は -128 となる）の値が入ります。マップのコリジョン ID が先に代入された場合、アクター / プレイヤー ID は取得されません。※ 8x8 タイルサイズのみ対応しています。

  ![actor_walkability_checker](https://github.com/user-attachments/assets/3e9047c7-851e-4afc-8534-1fdd778b5e97)

---
  
- Obstacle_Checker `[タイルの障害物の情報を取得する]`

  特定のタイル（X,Y）の障害物の情報（マップのコリジョンまたはアクター）を取得します。指定したタイル上にアクターが存在せず、かつコリジョンが無い場合は、指定した変数に 0 が代入されます。それ以外の場合は、コリジョン オブジェクトの ID 情報が代入されます。（例）変数に入る値 --> 障害物なし=0、障害物あり=コリジョン ID、またはマイナス値で表されたアクターの ID（プレイヤーの衝突判定も含める場合、プレイヤーの ID は -128 となる）の値が入ります。マップのコリジョン ID が先に代入された場合、アクター / プレイヤー ID は取得されません。※ 8x8 タイルサイズのみ対応しています。

  ![obstacle_checker](https://github.com/user-attachments/assets/acdb7f39-8023-4e32-ad93-7669a49aefff)

---

***Sprite_Tile_Replacer*** `[指定のスプライトタイルを置き換える（VRAM バンク切り替え可能）]`

  スプライトのタイルを指定のタイルで置き換えます。GBVM 命令の VM_ACTOR_REPLACE_TILE と機能的にはほぼ同じですが、v4.0.1 の時点では「カラーのみ」モード指定の際に拡張された VRAM バンクにアクセスできないため、VRAM バンクを指定できるようにして、GBVM 命令を書かなくてもイベントとして使えるようにしたプラグインです。

  ![sprite_tiles_replace_plugin_event](https://github.com/user-attachments/assets/86c5d6a6-7970-4433-b330-bafeb2b08653)

  <dl>
  <dt>アクター</dt>
  <dd>スプライトを保持するアクターを指定します</dd>
  <dt>VRAM バンク</dt>
  <dd>
    置き換え対象となるタイルがどのバンクにあるかに応じて 0 または 1 を指定します
    
  ![vram_banks_explained](https://github.com/user-attachments/assets/b96ea501-889b-43a9-91f1-4d82c9115780)
    
  </dd>
  <dt>タイルバンク</dt>
  <dd>置き換え元のタイルバンクを指定します</dd>
  <dt>タイルセット</dt>
  <dd>置き換え元のタイルセットを指定します</dd>
  <dt>背景タイルのインデックス</dt>
  <dd>置き換え元のタイルセットのインデックス（左上から 0 で始まります）を指定します</dd>
  <dt>スプライトタイルのインデックス</dt>
  <dd>置き換え先のスプライトタイルのインデックス（取得方法は後述）を指定します</dd>
  </dl>

___
  **スプライトタイルのインデックスを取得するには？**

  スプライトのタイルは VRAM バンク内の予測できない場所に散りばめられるようです。そのため、まずは置き換え対象となるタイルのインデックスを取得する必要があります。以下のようなイベントを作成して、同プラグインを用いて VRAM（バンク 0 および 1）を数字付きのタイルセット（プレースホルダ タイル）で埋めます。
  
  ![generate_placeholder_tiles](https://github.com/user-attachments/assets/202725fb-9261-4752-8fcc-70c21e99e692)

  すると、ゲーム実行時にタイル インデックスがあてられたスプライトが表示されるので、置き換え目的のインデックスを取得しやすくなります。
  なお、スプライトの `「右」反転して「左」向きフレームを自動生成` チェックボックスが有効になっている場合は、タイルセットも反転してしまいますので、ご注意ください。
  
  ![placeholder_tiles_applied](https://github.com/user-attachments/assets/49f250ca-a2a8-4f4b-9aa8-ddbc227a06a7)

  数字タイルセット画像は、プラグインフォルダに同梱されている「Number_Tiles_vram0.png」および「Number_Tiles_vram1.png」をサンプルとしてお使いいただけます。
  
  ![Number_Tiles_vram0](https://github.com/user-attachments/assets/7c995253-0f39-4c28-9d1f-62b2ec3cb3ad)
  ![Number_Tiles_vram1](https://github.com/user-attachments/assets/8050849f-af5d-4aac-a8cd-963ece7dd773)

