//
//  GPDEventCell.m
//  GPSDemo
//
//  Created by James Lee on 10/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDEventCell.h"

@implementation GPDEventCell

- (void)awakeFromNib {
    self.selectionStyle = UITableViewCellSelectionStyleNone;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
