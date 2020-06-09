/*
[note]
INNER JOIN movies ON directors.movie_id = movies.id
の部分は必要でしょうか？
movies テーブルに存在しない映画を意図的に排除しようとしているのでしょうか？（そうかもしれない…）
*/

SELECT DISTINCT people.name
FROM people
INNER JOIN directors ON people.id = directors.person_id
INNER JOIN movies ON directors.movie_id = movies.id
INNER JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE ratings.rating >= 9.0;
