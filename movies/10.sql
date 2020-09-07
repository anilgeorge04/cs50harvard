-- Directors with at least 9.0 rating movie
SELECT DISTINCT people.name AS Directors FROM people
JOIN directors ON people.id = directors.person_id
JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE ratings.rating >= 9.0;