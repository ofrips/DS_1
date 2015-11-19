#ifndef TRAINER_H_
#define TRAINER_H_

class Trainer {

public:
	Trainer();
	Trainer(const Trainer& trainer);
	Trainer& operator=(const Trainer& trainer);
	virtual ~Trainer();
}

#endif /* TRAINER_H_ */
