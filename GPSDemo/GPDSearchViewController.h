//
//  GPDSearchViewController.h
//  GPSDemo
//
//  Created by James Lee on 5/14/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDViewController.h"

typedef enum : NSUInteger {
    GPDSearchDisplayTile,
    GPDSearchDisplayFull,
} GPDSearchDisplayMode;

@interface GPDSearchViewController : GPDViewController <SCSearchFetcherListener, UICollectionViewDataSource, UICollectionViewDelegate>

@property (nonatomic, copy) NSString *searchQuery;
@property (assign, nonatomic) GPDSearchDisplayMode displayMode;

@end
