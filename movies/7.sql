-- Movies released in 2010 and their rating ordered
SELECT movies.title, ratings.rating FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.year = 2010 ORDER BY ratings.rating DESC, movies.title ASC;