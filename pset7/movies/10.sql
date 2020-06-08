SELECT DISTINCT people.name
FROM people
INNER JOIN directors ON people.id = directors.person_id
INNER JOIN movies ON directors.movie_id = movies.id
INNER JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE ratings.rating >= 9.0;
