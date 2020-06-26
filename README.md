#  CS50 2020 課題

Harvard大学のMOOC講座、 [CS50 2020](https://cs50.harvard.edu/x/2020/) の課題

## Week 0
使用言語: Scratch
- [Race](pset0/Race.sb3)
  - Scratch で好きにゲームを作る課題
  - 簡単なレースゲームを制作した

## Week 1
使用言語: C言語
- [Hello](pset1/hello/hello.c)
  - 「Ayaka」と名前を入力すると、「Hello, Ayaka」と出力するプログラム
  - [問題文](https://cs50.harvard.edu/x/2020/psets/1/hello/)
- Mario [Less](pset1/mario/less/mario.c)/[More](pset1/mario/more/mario.c)
  - 高さを入力すると階段状のブロックを出力するプログラム
    - [問題文](https://cs50.harvard.edu/x/2020/psets/1/mario/less/)
  - 上記の階段状のブロックを線対称にふたつ出力するプログラム
    - [問題文](https://cs50.harvard.edu/x/2020/psets/1/mario/more/)
- [Cash](pset1/cash/cash.c)
  - 金額を入力すると、お釣りのコインの枚数を出力するプログラム
  - [問題文](https://cs50.harvard.edu/x/2020/psets/1/cash/)
- [Credit](pset1/credit/credit.c)
  - Luhnアルゴリズムというクレジット番号の認証に用いるアルゴリズムを用いて、このクレジット番号が正しいか、およびカードブランドを出力するプログラム
  - [問題文](https://cs50.harvard.edu/x/2020/psets/1/credit/)

## Week 2
使用言語: C言語
- [Readability](pset2/readability/readability.c)
  - Coleman-Liau indexという式を用いて、100ワードあたりの文字数、文数から文章のリーダビリティを測るプログラム
  - [問題文](https://cs50.harvard.edu/x/2020/psets/2/readability/)
- [Caesar](pset2/caesar/caesar.c)
  - もとの単語から数文字をずらした暗号を出力するプログラム（ex. HELLO → IFMMP）
  - [問題文](https://cs50.harvard.edu/x/2020/psets/2/caesar/)
- [Substitution](pset2/substitution/substitution.c)
  - 各アルファベットに違うアルファベット文字をあてる暗号を出力するプログラム
  - [問題文](https://cs50.harvard.edu/x/2020/psets/2/substitution/)

## Week 3
使用言語: C言語
- [Plurality](pset3/plurality/plurality.c)
  - 多数決プログラム
  - [問題文](https://cs50.harvard.edu/x/2020/psets/3/plurality/)
- [Runoff](pset3/runoff/runoff.c)
  - 決選投票プログラム
  - [問題文](https://cs50.harvard.edu/x/2020/psets/3/runoff/)
- [Tideman](pset3/tideman/tideman.c)
  - 誰が勝数が多いか、誰がより差をつけて勝っているかで勝者を決めるプログラム
  - [問題文](https://cs50.harvard.edu/x/2020/psets/3/tideman/)

## Week 4
使用言語: C言語
- [Filter less](pset4/filter/less/helpers.c)
  - 画像用フィルター（グレースケール、セピア、反転、ブラー）
  - `helpers.c` のみ実装 
  - [問題文](https://cs50.harvard.edu/x/2020/psets/4/filter/less/)
- [Filter more](pset4/filter/more/helpers.c)
  - 画像用フィルター（グレースケール、反転、ブラー、エッジ検出）
  - `helpers.c` のみ実装 
  - [問題文](https://cs50.harvard.edu/x/2020/psets/4/filter/more/)
- [Recover](pset4/recover/recover.c)
  - バイナリファイルからJPEG画像を復旧させるプログラム
  - [問題文](https://cs50.harvard.edu/x/2020/psets/4/recover/)

## Week5
使用言語: C言語
- [Speller](pset5/speller/dictionary.c)
  - スペルチェッカープログラム。辞書に登録されたワードではなかったらスペルミスとする。
  - このプログラムでは、A-Zで分割された線形リストを利用しているが、最終的にはここからさらにスピードチューニングしたプログラムにすることが推奨されている。
  - `dictionary.c` のみの実装
  - [問題文](https://cs50.harvard.edu/x/2020/psets/5/speller/)

## Week6
使用言語: Python
- [Hello](pset6/hello/hello.py)
  - 「Ayaka」と名前を入力すると、「Hello, Ayaka」と出力するプログラム
  - WEEK1でC言語でも同じアルゴリズムのプログラムを書いている。
  - [問題文](https://cs50.harvard.edu/x/2020/psets/6/hello/)
- Mario [Less](pset6/mario/less/mario.py)/[More](pset6/mario/more/mario.py)
  - WEEK1でC言語でも同じアルゴリズムのプログラムを書いている。
  - 高さを入力すると階段状のブロックを出力するプログラム
    - [問題文](https://cs50.harvard.edu/x/2020/psets/6/mario/less/)
  - 上記の階段状のブロックを線対称にふたつ出力するプログラム
    - [問題文](https://cs50.harvard.edu/x/2020/psets/6/mario/more/)
- [Cash](pset6/cash/cash.py)
  - 金額を入力すると、お釣りのコインの枚数を出力するプログラム
  - WEEK1でC言語でも同じアルゴリズムのプログラムを書いている。
  - [問題文](https://cs50.harvard.edu/x/2020/psets/6/cash/)
- [Credit](pset6/credit/credit.py)
  - Luhnアルゴリズムというクレジット番号の認証に用いるアルゴリズムを用いて、このクレジット番号が正しいか、およびカードブランドを出力するプログラム
  - WEEK1でC言語でも同じアルゴリズムのプログラムを書いている。
  - [問題文](https://cs50.harvard.edu/x/2020/psets/6/credit/)
- [Readability](pset6/readability/readability.py)
  - Coleman-Liau indexという式を用いて、100ワードあたりの文字数、文数から文章のリーダビリティを測るプログラム
  - WEEK2でC言語でも同じアルゴリズムのプログラムを書いている。
  - [問題文](https://cs50.harvard.edu/x/2020/psets/6/readability/)
- [DNA](pset6/dna/dna.py)
  - DNAの配列のパターンが連続している部分（STR）を参照してCSVファイル上の人物と一致するかを判定するプログラム
  - [問題文](https://cs50.harvard.edu/x/2020/psets/6/dna/)

## WEEK7
使用言語: SQL, Python
- [Movies](pset7/movies)
  - データベースから問題文の条件と合致するデータを引っ張るSQL文
  - [問題文](https://cs50.harvard.edu/x/2020/psets/7/movies/)
- [House](pset7/houses)
  - ホグワーツ魔法学校の名簿リストをデータベースに保存したり、出力したりするPythonプログラム
  - [問題文](https://cs50.harvard.edu/x/2020/psets/7/houses/)

## WEEK8
使用言語: HTML/CSS, Python
- HomePage
  - Webページを作る課題
  - ちょうど個人のWebサイトをリニューアルしなきゃと思っていたので、それを作って提出した。
  - 本当は4ページ作ってリンクする条件も入っていたけど、載せるコンテンツがなかったので、このまま提出した。
  - https://ikeay.net
  -[問題文](https://cs50.harvard.edu/x/2020/tracks/web/homepage/)
- [Finance](pset8/finance)
  - 株の売り買いをシミュレーションするFlaskアプリケーション
  - [問題文](https://cs50.harvard.edu/x/2020/tracks/web/finance/)
