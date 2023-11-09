SELECT DISTINCT(name) FROM people, directors, movies, ratings
WHERE people.id = person_id
AND directors.movie_id = movies.id
AND movies.id = ratings.movie_id
AND rating >= 9.0;
