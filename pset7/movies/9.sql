WITH StarPerson AS (
    SELECT stars.person_id AS person_id
    FROM stars
    INNER JOIN movies ON stars.movie_id = movies.id
    WHERE movies.year = 2004
)

SELECT name
FROM people
WHERE id IN (SELECT * FROM StarPerson)
ORDER BY people.birth;
