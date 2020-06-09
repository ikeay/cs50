/*
[note]
LEFT OUTER JOIN stars

のところを外部結合にしたのはどういう意図でしょう？
INNER JOIN stars

で十分かと思いました。
*/
SELECT title
FROM movies
LEFT OUTER JOIN stars
ON movies.id = stars.movie_id
INNER JOIN people
ON people.id = stars.person_id
WHERE name = "Johnny Depp" OR name = "Helena Bonham Carter" -- [note] 折角他は丁寧に書いてるので(以下略)
GROUP BY title
HAVING COUNT(title) = 2;
