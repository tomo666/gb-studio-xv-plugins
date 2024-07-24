# gb-studio-xv-plugins
GB Studio 4 用の変なプラグイン集

## 概要
開発中のゲーム「XV」の副産物です。商用・非商用問わずご自由に改変してお使いください。

### 同梱物

*Obstacle_Checker*

- Actor_Walkability_Checker
- Obstacle_Checker

*SpriteTileReplace*
[指定のスプライトタイルを置き換える]

スプライトの背景タイルを指定のタイルで置き換えます。GBVM 命令の VM_ACTOR_REPLACE_TILE と機能的にはほぼ同じですが、v4.0.1 の時点では「カラーのみ」モード指定の際に拡張された VRAM バンクにアクセスできないため、VRAM バンクを指定できるようにして、GBVM 命令を書かなくてもイベントとして使えるようにしたプラグインです。

## 使い方

GB Studio プロジェクトフォルダの「plugins」フォルダに jaJP の中にあるフォルダをコピーしてください。

[イベントの追加] ダイアログの [XV プラグイン] カテゴリ以下から取り込みたいイベントを追加します。


![adding_plugin_events](https://github.com/user-attachments/assets/efd9f8f9-25b7-4d8b-b14e-651dd1d53da4)
