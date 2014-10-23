//
//  GPDSideMenuCell.m
//  GPSDemo
//
//  Created by James Lee on 5/10/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDSideMenuCell.h"

@implementation GPDSideMenuCell

- (void)awakeFromNib
{
//    for (NSString *font in [UIFont fontNamesForFamilyName:@"Open Sans"]) {
//        NSLog(@"%@",font);
//    }
    [self.titleLabel setFont:[UIFont fontWithName:@"OpenSans" size:18.0]];
    [self.titleLabel setTextColor:[UIColor colorWithWhite:1.0 alpha:0.8]];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
    UIColor *color = selected ? [UIColor colorWithWhite:1 alpha:0.4] : [UIColor colorWithWhite:1 alpha:0.8];
    [self.titleLabel setTextColor:color];
}

- (void)setHighlighted:(BOOL)highlighted animated:(BOOL)animated
{
    [super setHighlighted:(BOOL)highlighted animated:animated];
    UIColor *color = highlighted ? [UIColor colorWithWhite:1 alpha:0.35] : [UIColor colorWithWhite:1 alpha:0.8];
    [self.titleLabel setTextColor:color];
}

@end
