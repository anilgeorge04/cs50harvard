-- Avg Rating of all movies released in 2012
SELECT avg(ratings.rating) AS "2012 Avg Rating"
FROM ratings JOIN movies ON ratings.movie_id = movies.id
WHERE movies.year = 2012;