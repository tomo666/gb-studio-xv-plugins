# gb-studio-xv-plugins
GB Studio 4 用のプラグイン集

## 概要
GB Studio で開発中のゲーム「XV」の副産物です。現行バージョン（4.0.1）のイベントでは実現できない機能をプラグインとして実装しています。

- Actor_Walkability_Checker `[アクターの進行方向の障害物を取得する]`
- Obstacle_Checker `[タイルの障害物の情報を取得する]`
- SpriteTileReplace `[指定のスプライトタイルを置き換える]`

クセの強いプラグイン集なので万人向けではないかもしれませんが、役に立つ人もいるかもしれません。
商用・非商用問わずご自由にお使いください。ただし、これらのプラグイン集は実験的な制作物なので、将来予告なく改変・削除する可能性があります。また、バグや追加機能の追加は著者自身が必要としない場合は原則いたしませんので、利用はくれぐれも自己責任でお願いします。

クレジット記載などは不要ですが、クレジットいただける場合はこちらをお使いください：Tomo@indiegdevstdio または Tomo。

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

***Obstacle_Checker*** `[衝突判定用プラグイン集]`

- Actor_Walkability_Checker `[アクターの進行方向の障害物を取得する]`

  アクターの現在地と向きを基準にして、向かう方角に障害物が無く通行可能かどうかをチェックします。アクターが向いている方向にアクターがどのくらいのタイル数を進むかをオフセット値として指定し、アクターの現在位置から目的地の間に他のアクターが存在せず、かつコリジョンが無い場合は、障害物無しとみなされます。それ以外の場合は、衝突したオブジェクト（他のアクターまたはコリジョンが適用されたタイル）の ID 情報が代入されます。（例）変数に入る値 --> 障害物なし=0、障害物あり=コリジョン ID、またはマイナス値で表されたアクターの ID（ただし、プレイヤーの ID は -128 となる）の値が入ります。マップのコリジョン ID が先に代入された場合、アクター / プレイヤー ID は取得されません。※ 8x8 タイルサイズのみ対応しています。

  ![actor_walkability_checker](https://github.com/user-attachments/assets/3e9047c7-851e-4afc-8534-1fdd778b5e97)
  
- Obstacle_Checker `[タイルの障害物の情報を取得する]`

  特定のタイル（X,Y）の障害物の情報（マップのコリジョンまたはアクター）を取得します。指定したタイル上にアクターが存在せず、かつコリジョンが無い場合は、指定した変数に 0 が代入されます。それ以外の場合は、コリジョン オブジェクトの ID 情報が代入されます。（例）変数に入る値 --> 障害物なし=0、障害物あり=コリジョン ID、またはマイナス値で表されたアクターの ID（プレイヤーの衝突判定も含める場合、プレイヤーの ID は -128 となる）の値が入ります。マップのコリジョン ID が先に代入された場合、アクター / プレイヤー ID は取得されません。※ 8x8 タイルサイズのみ対応しています。

  ![obstacle_checker](https://github.com/user-attachments/assets/acdb7f39-8023-4e32-ad93-7669a49aefff)



***SpriteTileReplace*** `[指定のスプライトタイルを置き換える]`

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


