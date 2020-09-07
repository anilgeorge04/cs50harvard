-- Stars in movies released in 2004 ordered by age
SELECT people.name AS "Stars in 2004" FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE movies.year = 2004
GROUP BY people.id
ORDER BY people.birth ASC;