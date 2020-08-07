SELECT title
FROM movies
INNER JOIN stars
ON movies.id = stars.movie_id
INNER JOIN people
ON people.id = stars.person_id
WHERE name = "Johnny Depp" OR name = "Helena Bonham Carter"
GROUP BY title
HAVING COUNT(title) = 2;
