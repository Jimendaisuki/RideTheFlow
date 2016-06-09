#pragma once

/***����***/
//�ǂ̂��炢�J�����̑O�̏ꏊ�ɒʏ�U�����邩(�_�b�V�����͖���)
const float cameraFrontAttack = 10.0f;


/****�G�R��****/

//�R���̃X�s�[�h
const float ArmySpeed = 50.0f;
//�R���̍U���N�[���^�C��
const float ArmyAttackTime = 0.5f;
//�R���̍U���͈�
const float ArmyRange = 200.0f;
//�R�����v���C���[���猩�Ăǂ��܂ŋ߂Â���(�x��)�@�@��:0�x�ɂ����ꍇ�v���C���[�̐^���ɂ܂ŗ���
const float ArmyNear = 45.0f;
//�R�������ɔ��˂����̖{��
const int ArmyArrorwNum = 10;

//�R������v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float NotLookArmyAttackTime = 20.0f;
//�R������v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂����̖{��
const float NotLookArmyArrorwNum = 5;

//�R���̍U�����x
const float ArmyArrowAccuracy = 50.0f;
//�R���̍U��������̉e�����󂯂銄��
const float ArmyWindPercentage = 80.0f;


/****�G�o���X�^****/

//�o���X�^�̒e�X�s�[�h
const float VaristorSpeed = 3.0f;
//�o���X�^�̍U���N�[���^�C��
const float VaristorAttackTime = 5.0f;
//�o���X�^�����ɔ��˂����̐�
const int VaristorArrorwNum = 2;
//�o���X�^�̍U���͈�
const float VaristorRange = 300.0f;
//�o���X�^�����˂ł���Z�����ɂ����ō��p�x�i�x�j
const float VaristorAttackMaxAngle = 45.0f;
//�o���X�^�����˂ł���Z�����ɂ����ŏ��p�x�i�x�j
const float VaristorAttackMinAngle = -45.0f;
//�o���X�^�̏����x
const float VaristorInitialVelocity = 60.0f;
//�o���X�^�̐��񑬓x
const float VaristorSwingSpeed = 100.0f;

//�o���X�^����v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float NotLookVaristorAttackTime = 10.0f;
//�o���X�^����v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂����̖{��
const float NotLookVaristorArrowNum = 2;

//�o���X�^�U�����x(�������قǍ����x)
const float VaristorArrowAccuracy = 10.0f;
//�o���X�^�̍U��������̉e�����󂯂銄��
const float VaristorWindPercentage = 75.0f;



/****�G��C****/

//��C�̒e�X�s�[�h
const float CannonSpeed = 3.0f;
//��C�̍U���N�[���^�C��
const float CannonAttackTime = 0.1f;
//��C�̍U���͈�
const float CannonRange = 300.0f;
//��C�����ɔ��˂���C�e�̐�
const int CannonShellNum = 1;
//��C�̔��˂ł���Z�����ɂ����ō��p�x�i�x�j
const float  CannonAttackMaxAngle = 45.0f;
//��C�̔��˂ł���Z�����ɂ����Œ�p�x�i�x�j
const float CannonAttackMinAngle = -45.0f;
//��C�̋ʂ̏����x
const float CannonInitialVelocity = 100.0f;
//��C�̐��񑬓x
const float ConnonSwingSpeed = 50.0f;

//��C����v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float NotLookCannonAttackTime = 30.0f;
//��C����v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂���C�e�̐�
const float NotLookCannonShellNum = 1;

//��C�U�����x(�������قǍ����x)
const float CannonShellAccuracy = 10.0f;
//��C�̍U��������̉e�����󂯂銄��
const float CannonWindPercentage = 50.0f;


/****�G�̑D****/

//�D�̃X�s�[�h
const float ShipSpeed = 50.0f;
//�D�̒�ʒu�̍����ɖ߂�X�s�[�h
const float ShipDownSpeed = 10.0f;
//�D�̐��񑬓x
const float ShipSwingSpeed = 25.0f;
//�D�̍U��������̉e�����󂯂銄��
const float ShipWindPercentage = 100.0f;

//�D�o���X�^�̍U���N�[���^�C��
const float ShipVaristorAttackTime = 4.0f;
//�D�o���X�^�����ɔ��˂����̐�
const int ShipVaristorArrorwNum = 2;
//�D�o���X�^�̍U���͈�
const float ShipVaristorRange = 300.0f;
//�D�o���X�^�����˂ł���Z�����ɂ����ō��p�x�i�x�j
const float ShipVaristorAttackMaxAngle = 45.0f;
//�D�o���X�^�����˂ł���Z�����ɂ����ŏ��p�x�i�x�j
const float ShipVaristorAttackMinAngle = -45.0f;
//�D�o���X�^�̏����x
const float ShipVaristorInitialVelocity = 60.0f;
//�D�o���X�^�̐��񑬓x
const float ShipVaristorSwingSpeed = 100.0f;

//�D�o���X�^����v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float ShipNotLookVaristorAttackTime = 10.0f;
//�D�o���X�^����v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂����̖{��
const float ShipNotLookVaristorArrowNum = 2;


//�D��C�̍U���N�[���^�C��
const float ShipCannonAttackTime = 10.0f;
//�D��C�̍U���͈�
const float ShipCannonRange = 300.0f;
//�D��C�����ɔ��˂���C�e�̐�
const int ShipCannonShellNum = 1;
//�D��C�̔��˂ł���Z�����ɂ����ō��p�x�i�x�j
const float  ShipCannonAttackMaxAngle = 45.0f;
//�D��C�̔��˂ł���Z�����ɂ����Œ�p�x�i�x�j
const float ShipCannonAttackMinAngle = -45.0f;
//�D��C�̋ʂ̏����x
const float ShipCannonInitialVelocity = 100.0f;
//�D��C�̐��񑬓x
const float ShipConnonSwingSpeed = 50.0f;

//�D��C����v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float ShipNotLookCannonAttackTime = 30.0f;
//�D��C����v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂���C�e�̐�
const float ShipNotLookCannonShellNum = 1;


/***������***/

//�������̃N�[���^�C��
const float DoragonSpearAttackTime = 3.0f;
//�v���C���[�������������ɓ�����������U�����鎞�܂ł̎���
const float DoragonSpearWithinTime = 0.1f;
//���������ő�ɐL�т�܂ł̎���
const float DoragonSpearMaxTime = 10.0f;
//�����������S�ɏo�Ă����ɂƂǂ܂鎞��
const float DoragonSpearStopTime = 1.0f;
