-- Movies with IMDb rating of 10.0
SELECT COUNT(movies.id) AS "# of 10.0 rated movies" FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating = 10.0; 