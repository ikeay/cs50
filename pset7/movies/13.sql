WITH KevinBaconMovies AS (
    SELECT DISTINCT movies.id AS movie_id
    FROM movies
    INNER JOIN stars ON movies.id = stars.movie_id
    INNER JOIN people ON people.id = stars.person_id
    WHERE people.name = "Kevin Bacon" AND people.birth = 1958
)

SELECT DISTINCT name
FROM people
INNER JOIN stars ON people.id = stars.person_id
INNER JOIN movies ON movies.id = stars.movie_id
WHERE movies.id IN (SELECT movie_id FROM KevinBaconMovies)
    AND people.name != "Kevin Bacon";