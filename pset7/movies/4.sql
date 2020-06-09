/*
[note]
ここはmovies テーブルを参照する必要はなく、ratings テーブルのみを参照して
カウントするだけでもよいのでは？

ratings テーブルに存在してmovies テーブルに存在しないmovie_id があれば
話は変わってきますが、これは「レーティング情報はあるけど題名が登録されていない映画」
となり、データの整合性が取れていない状況のように思えます。
何かの問題が生じてこういったケースが発生することは考えられますが、
こういったケースを想定してINNER JOIN されたのでしょうか？
（題名が登録されているけどレーティング情報がない、という逆のケースは普通にあり得ます。）
*/
SELECT COUNT(*)
FROM movies
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating = 10.0;
