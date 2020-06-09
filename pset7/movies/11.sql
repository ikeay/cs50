SELECT movies.title
FROM movies
INNER JOIN stars ON movies.id = stars.movie_id
INNER JOIN people ON people.id = stars.person_id
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name = "Chadwick Boseman"
-- [note] 折角他は丁寧に書いてるので、ここもratings.rating にしておいてよいのでは？（＾＾；
ORDER BY rating DESC
LIMIT 5;
