# encoding: utf-8


from .baseline import Baseline


def build_model(cfg, num_classes):
    # if cfg.MODEL.NAME == 'resnet50':
    #     model = Baseline(num_classes, cfg.MODEL.LAST_STRIDE, cfg.MODEL.PRETRAIN_PATH, cfg.MODEL.NECK, cfg.TEST.NECK_FEAT)
    model = Baseline(num_classes, cfg.MODEL.NAME, cfg.MODEL.PRETRAIN_PATH, cfg.MODEL.LAST_STRIDE)
    return model
